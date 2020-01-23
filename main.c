// Copyright 2019 EvilBorsch"
#include <assert.h>
#include "libdynamic.h"
#include "libstatic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * В вашем распоряжении — нижняя треугольная матрица, полученная из воображаемой
 квадратной матрицы размером 100 000 x 100 000
 * и заполненная значениями от 0 до 3. Предложите эффективную организацию ее
 хранения в памяти,
 * инициализируйте матрицу и найдите сумму последних элементов в каждой ее
 строке (элементов диагонали)
 * с помощью последовательного и параллельного с использованием нескольких
 процессов алгоритмов
 * с учётом оптимизации работы с кэш-памятью.

 */

#define MIN_NUMBER 0
#define MAX_NUMBER 3
void test();
void del_mat(char **mat, size_t n);
char **init_matrix_from_keyboard(size_t n);
char **init_with_num(size_t n, char num);

int main() {
  test();
  return 0;
}

void test() {
  {
    int n = 100;
    char **mat = init_with_num(n, 2);
    size_t k = 0;
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j <= k; j++) {
        assert(2 == (mat[i][j]));
      }
      k++;
    }
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 3;
    char **mat = init_with_num(n, 1);
    mat[0][0] = (1);
    mat[1][1] = (2);
    mat[2][2] = (3);
    assert(get_sigma_diagonal(mat, n) == 6);
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 3;
    char **mat = init_with_num(n, 1);
    assert(get_sigma_diagonal(mat, n) == n);
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 5;
    char **mat = init_with_num(n, 3);
    assert(get_sigma_diagonal(mat, n) == summa_diagonali(4, mat, n));
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 100;
    char **mat = init_with_num(n, 1);
    assert(summa_diagonali(4, mat, n) == n);
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 100;
    char **mat = init_with_num(n, 1);
    assert(get_sigma_diagonal(mat, n) == summa_diagonali(4, mat, n));
    del_mat(mat, n);
    printf("%s\n", "OK");
  }

  {
    int n = 30000;
    char **mat = init_with_num(n, 1);
    assert(summa_diagonali(4, mat, n) == n);
    del_mat(mat, n);
    printf("%s\n", "OK");
  }
}

void del_mat(char **mat, const size_t n) {
  if (mat == NULL) {
    perror("mat is null");
    return;
  }
  for (size_t i = 0; i < n; i++) {
    free(mat[i]);
  }
  free(mat);
}

char **init_matrix_from_keyboard(const size_t n) {
  char **mat = (char **)malloc(n * sizeof(char *));
  if (mat == NULL) {
    perror("MEMORY ERROR");
    return NULL;
  }

  size_t k = 0;

  for (size_t i = 0; i < n; i++) {
    mat[i] = (char *)malloc(sizeof(char) * (k + 1));
    if (mat[i] == NULL) {
      perror("MEMMORY ERROR");
      free(mat);
      return NULL;
    }

    for (size_t j = 0; j <= k; j++) {
      char chis;
      scanf("%c", &chis);
      if (chis < MIN_NUMBER || chis > MAX_NUMBER) {
        free(mat[i]);
        perror("BAD NUM");
        return NULL;
      }
      mat[i][j] = chis;
    }
    k++;
  }
  return mat;
}

char **init_with_num(const size_t n, const char num) {
  char **mat = (char **)malloc(n * sizeof(char *));
  if (mat == NULL) {
    perror("MEMMORY ERROR");
    return NULL;
  }
  size_t k = 0;
  for (size_t i = 0; i < n; i++) {
    mat[i] = (char *)malloc(sizeof(char) * (k + 1));
    if (mat[i] == NULL) {
      perror("MEMMORY ERROR");
      free(mat);
      return NULL;
    }
    for (size_t j = 0; j <= k; j++) {
      mat[i][j] = num;
    }
    k++;
  }
  return mat;
}
