#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if (columns < 1 || rows < 1) {
    error = 1;
  } else {
    result->matrix = (double **)calloc(sizeof(double *), rows);
    if (result->matrix == NULL) {
      error = 1;
    }
    if (!error) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(sizeof(double), columns);
        if (result->matrix[i] == NULL) {
          error = 1;
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          i = rows;
        }
      }
    }
  }
  if (error == 1) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (!s21_matrix_null(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_matrix_null(matrix_t *A) {
  int error = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    error = 1;
  }
  return error;
}
