// Copyright 2019 EvilBorsch
#include <errno.h>
#include "libdynamic.h"
#include <stdlib.h>
#include <unistd.h>

int process_summ_last_matrix_elements(int started_str, char** matrix, int N,
                                      int chisyad) {
  if (matrix == NULL) {
    exit(EMSGSIZE);
  }
  int result = 0;
  int kolvostrok = N / chisyad;
  if (started_str == (chisyad - 1) * kolvostrok) {
    kolvostrok = N - started_str;
  }
  printf("start: %d", started_str);
  printf("kolvo: %d\n", kolvostrok);
  for (int i = started_str; i < started_str + kolvostrok; i++) {
    result += matrix[i][i];
  }
  return result;
}

int summa_diagonali(int core_count, char** matrix, const int N) {
  int* pid = malloc((core_count + 1) * sizeof(int));
  int status = 0;
  int fd[2];
  pipe(fd);
  int d = 0;
  for (int i = 0; i < N; i += N / core_count) {
    pid[d] = fork();

    if (pid[d] == -1) {
      exit(EAGAIN);
    }

    if (pid[d] == 0) {
      close(fd[0]);
      int* ans = malloc(sizeof(int));
      ans[0] = process_summ_last_matrix_elements(i, matrix, N, core_count);

      write(fd[1], ans, sizeof(int));
      free(ans);
      exit(EXIT_SUCCESS);
    }
    d++;
  }

  for (size_t c = 0; c < core_count; ++c) {
    waitpid(pid[c], &status, 0);
  }
  close(fd[1]);

  int* buf = malloc(sizeof(int) * core_count);

  int answer = 0;

  read(fd[0], buf, core_count * sizeof(int));

  for (size_t c = 0; c < core_count; ++c) {
    answer += buf[c];
  }

  free(buf);
  free(pid);
  return answer;
}
