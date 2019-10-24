// Copyright 2019 EvilBorsch
#include <stdio.h>
#include <stdlib.h>
#include "libstatic.h"

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
      scanf("%d", &chis);
      if (chis < 0 || chis > 3) {
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

void del_mat(char **mat, const size_t n) {
  for (size_t i = 0; i < n; i++) {
    free(mat[i]);
  }
  free(mat);
}

int get_sigma_diagonal(char **mat, const size_t n) {
  size_t sigma = 0;
  for (size_t i = 0; i < n; i++) {
    sigma += (mat[i][i]);
  }
  return sigma;
}
