
/* Create macros so that the matrices are stored in column-major order */
#include <stdio.h>

#include "matmul.h"

#undef A
#undef B
#undef C

#define A(i, j) a[(j)*lda + (i)]
#define B(i, j) b[(j)*ldb + (i)]
#define C(i, j) c[(j)*ldc + (i)]

/* Routine for computing C = A * B + C */
// col-major
void matmul_ref(int m, int n, int k,
                float *a, int lda,
                float *b, int ldb,
                float *c, int ldc)
{
  int i, j, p;

  for (i = 0; i < lda; i++)
  {
    for (j = 0; j < ldb; j++)
    {
      for (p = 0; p < k; p++)
      {
        C(i, j) += A(i, p) * B(p, j);
      }
    }
  }
}