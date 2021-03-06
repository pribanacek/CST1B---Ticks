#include "matrix.h"
#include <stdbool.h>

matrix_t matrix_create(int rows, int cols) {
  double *elts = malloc(rows * cols * sizeof(double));
  matrix_t m = {rows, cols, elts};
  return m;
}

double matrix_get(matrix_t m, int r, int c) {
  assert(r < m.rows && c < m.cols);
  return m.elts[r * m.cols + c];
}

void matrix_set(matrix_t m, int r, int c, double d) {
  assert(r < m.rows && c < m.cols);
  m.elts[r * m.cols + c] = d;
}


void matrix_free(matrix_t m) {
  free(m.elts);
}

matrix_t matrix_multiply(matrix_t m1, matrix_t m2) {
  assert(m1.cols == m2.rows);

  matrix_t m = matrix_create(m1.rows, m2.cols);

  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.cols; j++) {
      double sum = 0.0;
      for (int l = 0; l < m1.cols; l++) {
        sum += matrix_get(m1, i, l) * matrix_get(m2, l, j);
      }
      matrix_set(m, i, j, sum);
    }
  }

  return m;
}

matrix_t matrix_transpose(matrix_t m) {
  matrix_t t = matrix_create(m.cols, m.rows);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {
      double a = matrix_get(m, i, j);
      matrix_set(t, j, i, a);
    }
  }
  return t;
}

matrix_t matrix_multiply_transposed(matrix_t m1, matrix_t m2) {
  assert(m1.cols == m2.cols);

  matrix_t m = matrix_create(m1.rows, m2.rows);

  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.rows; j++) {
      double sum = 0.0;
      for (int l = 0; l < m1.cols; l++) {
        sum += matrix_get(m1, i, l) * matrix_get(m2, j, l);
      }
      matrix_set(m, i, j, sum);
    }
  }

  return m;
}

matrix_t matrix_multiply_fast(matrix_t m1, matrix_t m2) {
  matrix_t trans = matrix_transpose(m2);
  matrix_t result = matrix_multiply_transposed(m1, trans);
  matrix_free(trans);
  return result;
}

void matrix_print(matrix_t m) {
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.cols; j++) {
      printf("%g\t", matrix_get(m, i, j));
    }
    printf("\n");
  }
  printf("\n");
}
