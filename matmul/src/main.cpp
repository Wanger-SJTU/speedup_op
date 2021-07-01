
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

#include "matmul.h"

using namespace std;

int set_sched_affinity(const std::vector<int> cpu_ids) {

// set affinity for thread
#ifdef __GLIBC__
  pid_t pid = syscall(SYS_gettid);
#else
  pid_t pid = gettid();
#endif
  cpu_set_t mask;
  CPU_ZERO(&mask);
  for (int i = 0; i < cpu_ids.size(); ++i) {
    CPU_SET(cpu_ids[i], &mask);
  }
  int syscallret = syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);
  if (syscallret) {
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf("too few args\n");
    return 0;
  }

  set_sched_affinity({7});

  int params[3]; // m k n
  for (int i = 1; i < 4; ++i) {
    params[i - 1] = stoi(argv[i]);
  }

  float *a = new float[params[0] * params[1]]; // m * k
  float *b = new float[params[1] * params[2]]; // k * n
  float *c = new float[params[0] * params[2]]; // m * n
  memset(c, 0, params[0] * params[2] * sizeof(float));

  test_acc(params[0], params[1], params[2], a, b, c);

  double gflops = 2 * params[0] * params[2] * params[1] * 1e-9;
  int run_cnt = 5000;
  struct timeval t1, t2;

  printf("======== warm up ======\n");
  for (int i = 0; i < 50; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  printf("========== start ======\n");

  auto time = clock();
  for (int i = 0; i < run_cnt; ++i) {
    matmul(params[0], params[1], params[2], a, b, c);
  }
  time = clock() - time;
  // gettimeofday(&t2, nullptr);

  // double timeuse = (t2.tv_sec - t1.tv_sec);
  double timeuse = (time * 1.0) / CLOCKS_PER_SEC;

  printf("===========result=======\n");
  printf(" use time   | %.3f ms     \n", timeuse / run_cnt * 1000);
  printf(" GFLOPS     | %.3f     \n", gflops * run_cnt / (timeuse + 1e-6));
  printf("===========end==========\n");

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}