#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>

int K;
int M;
int N;
double (*A_ptr);
double (*B_ptr);
double (*C_ptr);

void allocate_arrays() {
  A_ptr = malloc(sizeof(double) * (M) * (K));
  B_ptr = malloc(sizeof(double) * (K) * (N));
  C_ptr = malloc(sizeof(double) * (M) * (N));
}

float frand(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

int irand(int min, int max) {
  return min + (rand() % (max - min + 1));
}

double drand(double min, double max) {
  double scale = rand() / (double) RAND_MAX;
  return min + scale * (max - min);
}

void init_scalars(int inputs[16]) {
  K = inputs[2];
  M = inputs[0];
  N = inputs[1];
}

void init_arrays(double (*restrict A)[M][K], double (*restrict B)[K][N], double (*restrict C)[M][N]) {
  for (int i0 = 0; i0 <= M - 1; i0 += 1) {
    for (int i1 = 0; i1 <= K - 1; i1 += 1) {
      (*A)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= K - 1; i0 += 1) {
    for (int i1 = 0; i1 <= N - 1; i1 += 1) {
      (*B)[i0][i1] = drand(0.0, 1.0);
    }
  }
  for (int i0 = 0; i0 <= M - 1; i0 += 1) {
    for (int i1 = 0; i1 <= N - 1; i1 += 1) {
      (*C)[i0][i1] = drand(0.0, 1.0);
    }
  }
}

void init_array_ptrs() {
  init_arrays((double(*)[M][K])(A_ptr), (double(*)[K][N])(B_ptr), (double(*)[M][N])(C_ptr));
}

void measure_init_();
void measure_start_();
void measure_stop_();

int core(double (*restrict A)[M][K], double (*restrict B)[K][N], double (*restrict C)[M][N]);

void measure(int n_iterations, int inputs[16]) {
  srand(0);
  init_scalars(inputs);
  allocate_arrays();
  init_array_ptrs();

  printf("inputs are M(%d) N(%d) K(%d)\n", M, N, K);
  measure_init_();
  measure_start_();
  clock_t start = clock();
  for (int i = 0; i < n_iterations; ++i) {
    core((double(*)[M][K])(A_ptr), (double(*)[K][N])(B_ptr), (double(*)[M][N])(C_ptr));
  }
  clock_t end = clock();

  uint64_t cpu_time_ns = ((double)(end - start)) / CLOCKS_PER_SEC * 1e9;
  FILE *f;
  f = fopen("codelet_info.txt", "w");
  fprintf(f, "# n_iterations M N K cpu_time_ns\n");
  fprintf(f, "%d %d %d %d %" PRIu64 "\n", n_iterations, M, N, K, cpu_time_ns);
  fclose(f);

  measure_stop_();
}
