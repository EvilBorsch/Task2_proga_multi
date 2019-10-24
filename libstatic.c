// Copyright 2019 EvilBorsch
#include <stdio.h>
#include "libstatic.h"

#define MEMMORY_ERROR 28

int get_sigma_diagonal(char **mat, const size_t n) {
  if (mat == NULL) {
    perror("Mat is null");
    return MEMMORY_ERROR;
  }
  size_t sigma = 0;
  for (size_t i = 0; i < n; i++) {
    sigma += (mat[i][i]);
  }
  return sigma;
}
