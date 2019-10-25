// Copyright 2019 EvilBorsch
#include "libdynamic.h"
#include <stdlib.h>
#include <unistd.h>

#define PROCESS_ERROR 15

int process_summ_last_matrix_elements(int started_str, char **matrix, int N,
                                      int chisyad) {
  int result = 0;
  int kolvostrok = N / chisyad;
  if (started_str == (chisyad - 1) * kolvostrok) kolvostrok = N - started_str;

  for (int i = started_str; i < started_str + kolvostrok; i++) {
    result += matrix[i][i];
  }
  return result;
}

int summa_diagonali(int chisyad, char **matrix, int N) {
  int status;
  int okonch_result = 0;

  int fd[2];
  pipe(fd);
  int pid = 0;
  int started_str = 0;
  for (int i = 0; i <= (chisyad - 1) * N / chisyad; i += N / chisyad) {
    pid = fork();
    if (-1 == pid) {
      exit(PROCESS_ERROR);
    } else if (0 == pid) {
      started_str = i;
      break;
    }
  }

  if (pid == 0) {
    int ans[1];
    ans[0] = process_summ_last_matrix_elements(started_str, matrix, N, chisyad);
    close(fd[0]);
    write(fd[1], ans, sizeof(ans));
    exit(0);
  }

  waitpid(pid, &status, 0);
  int buf[chisyad];
  read(fd[0], buf, sizeof(buf) * chisyad);
  for (int i = 0; i < chisyad; i++) {
    okonch_result = okonch_result + buf[i];
  }
  close(fd[1]);
  return okonch_result;
}
