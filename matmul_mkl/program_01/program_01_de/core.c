#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include "mkl.h"

extern int K;
extern int M;
extern int N;

int core(double *restrict A_ptr, double *restrict B_ptr, double *restrict C_ptr, int n_iterations) {
  double alpha = 1.0;
  double beta = 0.0;

  for (int i = 0; i < n_iterations; ++i) {
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
    		M, N, K, alpha, A_ptr, K, B_ptr, N, beta, C_ptr, N);
  }
  return 0;
}

