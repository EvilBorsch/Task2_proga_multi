
#include <assert.h>
#include "libdynamic.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ERROR 228;


typedef struct {
    int rowSize; //размер строки
    int started_str;
    int num_of_strs;
    char **matrix;
} pthrData;

static long int result = 0;


void *summ_last_elements(void *stroki) {
    //получаем структуру с данными
    pthrData *data = (pthrData *) stroki;
    assert(data != NULL);
    int k = (data->rowSize) - 1;
    if (k < 0) k = 0;

    for (int i = data->started_str; i < data->started_str + data->num_of_strs; i++) {
        result += data->matrix[i][k];
        ++k;

    }

    return NULL;
}

long int find_sigma_diagonals(char **matrix1, int N) {
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

    pthread_t *threads = (pthread_t *) malloc(num_threads * sizeof(pthread_t));
    assert(threads != NULL);
    pthrData *threadData = (pthrData *) malloc(num_threads * sizeof(pthrData));
    assert(threadData != NULL);

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
    pthread_create(&(threads[num_threads - 1]), NULL, summ_last_elements, &threadData[num_threads - 1]);

    for (int i = 0; i < num_threads; i++) pthread_join(threads[i], NULL);
    free(threads);
    free(threadData);
    long int answer = result;
    result = 0;
    return answer;

}



