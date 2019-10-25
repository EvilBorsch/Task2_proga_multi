// Copyright 2019 EvilBorsch
#include <unistd.h>
#include "libdynamic.h"
#include <stdio.h>
#include <stdlib.h>


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
  int previous_started_str = 0;
  for (int i = 0; i < chisyad; i++) {
    int fd[2];
    pipe(fd);
    int buff[1];
    buff[0] = previous_started_str;
    previous_started_str = previous_started_str + N / chisyad;

    write(fd[1], buff,
          sizeof(buff) + 1);  // передаем в процесс строку с которой начинаем
    // подсчет элементов на диагонале для данного процесса
    int pid = fork();
    if (-1 == pid) {
      perror("Process Eroor");
      break;
    } else if (0 == pid) {
      int ans[1];
      int data[1];
      read(fd[0], data, sizeof(data) + 1);  // Берем строку с которой считаем
      int process_started_str = data[0];
      ans[0] = process_summ_last_matrix_elements(process_started_str, matrix, N,
                                                 chisyad);
      close(fd[0]);
      write(fd[1], ans,
            sizeof(ans) + 1);  // Кидаем в главный процесс посчитанную часть
      exit(0);
    }
    waitpid(pid, &status, 0);
    int buf[1];
    read(fd[0], buf, sizeof(buf));  // получаем из процесса посчитанную часть
    // printf("Received %d\n", buf[0]);
    okonch_result = okonch_result + buf[0];  // суммируем посчитанные части
    close(fd[1]);
  }
  return okonch_result;
}
