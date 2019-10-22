// Copyright 2019 EvilBorsch
#include "libdynamic.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>

#define MEMORY_ERROR 28;

typedef struct {
  int rowSize;
  int started_str;
  int num_of_strs;
  char **matrix;
} pthrData;

static int16_t result = 0;

void *summ_last_elements(void *stroki) {
  pthrData *data = (pthrData *)stroki;
  if (data == NULL) {
    free(data);
    perror("Memmory error");
    return NULL;
  }
  int k = (data->rowSize) - 1;
  if (k < 0) k = 0;

  for (int i = data->started_str; i < data->started_str + data->num_of_strs;
       i++) {
    result += data->matrix[i][k];
    ++k;
  }

  return NULL;
}

int16_t find_sigma_diagonals(char **matrix1, size_t N) {
  if (matrix1 == NULL || N < 0) {
    perror("MEMMORY_ERROR");
    return MEMORY_ERROR;
  }
  int num_threads = 4;

  if (N < 4 && N > 1) {
    num_threads = 2;
  }

  if (N == 1) {
    return matrix1[0][0];
  }

  pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
  if (threads == NULL) {
    perror("MEMMORY ERROR");
    free(threads);
    return MEMORY_ERROR;
  }
  pthrData *threadData = (pthrData *)malloc(num_threads * sizeof(pthrData));
  if (threadData == NULL) {
    perror("MEMMORY ERROR");
    free(threadData);
    return MEMORY_ERROR;
  }

  int previous_started_string = 0;
  for (int i = 0; i < num_threads - 1; i++) {
    threadData[i].rowSize = i;
    threadData[i].started_str = previous_started_string;
    threadData[i].matrix = matrix1;
    threadData[i].num_of_strs = N / num_threads;
    previous_started_string += N / num_threads;
    pthread_create(&(threads[i]), NULL, summ_last_elements, &threadData[i]);
  }
  threadData[num_threads - 1].rowSize = num_threads;
  threadData[num_threads - 1].started_str = previous_started_string;
  threadData[num_threads - 1].num_of_strs = N - previous_started_string;
  threadData[num_threads - 1].matrix = matrix1;
  pthread_create(&(threads[num_threads - 1]), NULL, summ_last_elements,
                 &threadData[num_threads - 1]);

  for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);
  free(threads);
  free(threadData);
  int16_t answer = result;
  result = 0;
  return answer;
}
