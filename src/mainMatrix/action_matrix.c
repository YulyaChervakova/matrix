#include "../s21_matrix.h"
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A)) {
    if (!s21_create_matrix(A->columns, A->rows, result)) {
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          result->matrix[i][j] = A->matrix[j][i];
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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (!s21_matrix_null(A)) {
    if (A->rows == A->columns) {
      if (!s21_create_matrix(A->columns, A->rows, result)) {
        if (A->columns == 2 && A->rows == 2) {
          result->matrix[0][0] = A->matrix[1][1];
          result->matrix[0][1] = -A->matrix[1][0];
          result->matrix[1][0] = -A->matrix[0][1];
          result->matrix[1][1] = A->matrix[0][0];
        } else {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->rows; j++) {
              if (A->columns == 3 && A->rows == 3) {
                result->matrix[i][j] =
                    s21_minor_two(A, i, j) * pow((-1), (i + 1) + (j + 1));
              } else {
                result->matrix[i][j] =
                    s21_minor(A, i, j) * pow((-1), (i + 1) + (j + 1));
              }
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
double s21_minor_two(matrix_t *A, int i, int j) {
  int k1 = 0;
  int m1 = 0;
  double rezult = 0;
  matrix_t minorMin;
  s21_create_matrix(A->rows - 1, A->columns - 1, &minorMin);
  for (int k = 0; k < A->rows - 1; k++) {
    if (k == i) k1 = 1;
    m1 = 0;
    for (int m = 0; m < A->columns - 1; m++) {
      if (m == j) m1 = 1;
      minorMin.matrix[k][m] = A->matrix[k + k1][m + m1];
    }
  }
  rezult = minorMin.matrix[0][0] * minorMin.matrix[1][1] -
           minorMin.matrix[1][0] * minorMin.matrix[0][1];
  s21_remove_matrix(&minorMin);
  return rezult;
}

double s21_minor(matrix_t *A, int i, int j) {
  int k1 = 0;
  int m1 = 0;
  matrix_t minorMin;
  s21_create_matrix(A->rows - 1, A->columns - 1, &minorMin);
  double rezult1 = 0;
  double rezult = 0;
  for (int k = 0; k < A->rows - 1; k++) {
    if (k == i) k1 = 1;
    m1 = 0;
    for (int m = 0; m < A->columns - 1; m++) {
      if (m == j) m1 = 1;
      minorMin.matrix[k][m] = A->matrix[k + k1][m + m1];
    }
  }
  for (int k = 0; k < A->columns - 1; k++) {
    rezult1 = 1;
    k1 = k;
    for (int m = 0; m < A->rows - 1; m++) {
      if (k1 == A->columns - 1) {
        k1 = 0;
      }
      rezult1 *= minorMin.matrix[m][k1];
      k1++;
    }
    rezult += rezult1;
  }
  for (int k = 0; k < A->columns - 1; k++) {
    rezult1 = 1;
    k1 = k;
    for (int m = 0; m < A->rows - 1; m++) {
      if (k1 == -1) {
        k1 = A->columns - 2;
      }
      rezult1 *= minorMin.matrix[m][k1];
      k1--;
    }
    rezult -= rezult1;
  }
  s21_remove_matrix(&minorMin);
  return rezult;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (result != NULL && !s21_matrix_null(A)) {
    *result = 0;
    if (A->rows == A->columns) {
      if (A->columns == 2 && A->rows == 2) {
        *result = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[1][0] * A->matrix[0][1]);
      } else {
        if (A->columns == 1 && A->rows == 1) {
          *result = A->matrix[0][0];
        } else {
          if (A->columns == 3 && A->rows == 3) {
            for (int j = 0; j < A->columns; j++) {
              *result = *result + (A->matrix[0][j] * s21_minor_two(A, 0, j)) *
                                      pow((-1), (j));
            }
          } else {
            for (int j = 0; j < A->columns; j++) {
              *result = *result +
                        (A->matrix[0][j] * s21_minor(A, 0, j)) * pow((-1), (j));
            }
          }
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

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  double determint;
  matrix_t oneResult;
  matrix_t lastResult;
  if (!s21_matrix_null(A) && result != NULL) {
    s21_determinant(A, &determint);
    if (A->rows == A->columns && determint != 0) {
      if (!s21_create_matrix(A->rows, A->columns, result)) {
        error = s21_calc_complements(A, &oneResult);
        if (error == 0) {
          error = s21_transpose(&oneResult, &lastResult);
          if (error == 0) {
            for (int i = 0; i < A->rows; i++) {
              for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = lastResult.matrix[i][j] / determint;
              }
            }
            s21_remove_matrix(&lastResult);
            s21_remove_matrix(&oneResult);
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
