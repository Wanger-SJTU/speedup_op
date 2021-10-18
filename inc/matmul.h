
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <vector>

/* Routine for computing C = A * B + C */
/*
  suppose a b c are col-major
  then A[i,j] = A[(j) * row + i]
*/

void matmul(int m, int n, int k, float *a, float *b, float *c);

void matmul_ref(int m, int k, int n, float *a, float *b, float *c);

bool test_acc(int m, int k, int n);
void print_matrix(int m, int n, float *a);
bool compare_matrix(int m, int n, float *a, float *ref);
void set_matrix_value(int m, int n, float *a);

void eval_gflops(int m, int k, int n, float *a, float *b, float *c);
int set_sched_affinity(const std::vector<int> cpu_ids);