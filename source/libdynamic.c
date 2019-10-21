//
// Created by Дмитрий Гуляченков on 21.10.2019.
//

#include "../libdynamic.h"
#include <stdio.h>
#include "../libstatic.h"
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct {
    int rowSize; //размер строки
    int start_str;
    int num_of_strs;
    char **matrix;
} pthrData;

static long int result = 0;


void *threadFunc(void *thread_data) {
    //получаем структуру с данными
    pthrData *data = (pthrData *) thread_data;
    int k = (data->rowSize) - 1;
    for (int i = data->start_str; i < data->start_str + data->num_of_strs; i++) {
        result += data->matrix[i][k];
        k++;

    }

    return NULL;
}

long int find_sigma_diagonals(char **matrix1, int N) {
    int NUM_THREADS = 4;
    if (N < 4 && N > 1) NUM_THREADS = 2;
    if (N == 1) return matrix1[0][0];

    pthread_t *threads = (pthread_t *) malloc(NUM_THREADS * sizeof(pthread_t));
    assert(threads != NULL);
    pthrData *threadData = (pthrData *) malloc(NUM_THREADS * sizeof(pthrData));
    assert(threadData != NULL);
    int prev_start = 0;

    for (int i = 0; i < NUM_THREADS - 1; i++) {
        threadData[i].rowSize = i;
        threadData[i].start_str = prev_start;
        threadData[i].matrix = matrix1;
        threadData[i].num_of_strs = N / NUM_THREADS;
        prev_start += N / NUM_THREADS;
        pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
    }
    threadData[NUM_THREADS - 1].rowSize = NUM_THREADS;
    threadData[NUM_THREADS - 1].start_str = prev_start;
    threadData[NUM_THREADS - 1].num_of_strs = N - prev_start;
    threadData[NUM_THREADS - 1].matrix = matrix1;
    pthread_create(&(threads[NUM_THREADS - 1]), NULL, threadFunc, &threadData[NUM_THREADS - 1]);

    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < NUM_THREADS; i++) pthread_cancel(threads[i]);
    free(threads);
    free(threadData);
    long int temp = result + matrix1[0][0];
    result = 0;
    return temp;

}



