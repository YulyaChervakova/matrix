#include "../s21_matrix.h"
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (!s21_matrix_null(A) && !s21_matrix_null(B) && A->rows == B->rows &&
      A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] - B->matrix[i][j] > 1e-06) {
          error = FAILURE;
        }
      }
    }
  } else {
    error = FAILURE;
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A) && !s21_matrix_null(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        error = 2;
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A) && !s21_matrix_null(B)) {
    if (A->rows == B->rows && A->columns == B->columns) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        error = 2;
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A)) {
    if (!s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A) && !s21_matrix_null(B)) {
    if (A->columns == B->rows) {
      if (!s21_create_matrix(A->rows, B->columns, result)) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      } else {
        error = 2;
      }
    } else {
      error = 2;
    }
  } else {
    error = 1;
  }
  return error;
}
