#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>

extern int K;
extern int M;
extern int N;

int core(double (*restrict A)[M][K], double (*restrict B)[K][N], double (*restrict C)[M][N]) {

#pragma omp parallel for private(i, j, k)
  for (int i = 0; i <= M - 1; i += 1) {
    double sum = 0.0;
    for (int j = 0; j <= N - 1; j += 1) {
      sum = 0;
      for (int k = 0; k <= K - 1; k += 1) {
        sum = sum + (*A)[i][k] * (*B)[k][j];
      }
      (*C)[i][j] = (*C)[i][j] + sum;
    }
  }
  return 0;
}
