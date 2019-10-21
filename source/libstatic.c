#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../libstatic.h"


char **init_matrix_from_keyboard(size_t n) {

    char **mat = (char **) malloc(n * sizeof(char *));
    assert(mat != NULL);
    size_t k = 0;

    for (size_t i = 0; i < n; i++) {
        mat[i] = (char *) malloc(sizeof(char) * (k + 1));
        assert(mat[i] != NULL);
        for (size_t j = 0; j <= k; j++) {
            int chis;
            scanf("%d", &chis);
            mat[i][j] = (char) chis;
        }
        k++;
    }
    return mat;
}


char **init_with_num(size_t n, int num) {
    char t = (char) num;

    char **mat = (char **) malloc(n * sizeof(char *));
    assert(mat != NULL);
    size_t k = 0;
    for (size_t i = 0; i < n; i++) {
        mat[i] = (char *) malloc(sizeof(char) * (k + 1));
        assert(mat[i] != NULL);
        for (size_t j = 0; j <= k; j++) {
            mat[i][j] = t;
        }
        k++;
    }
    return mat;
}


void print_mat(char **mat, size_t n) {
    size_t k = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j <= k; j++) {
            printf("%d ", (mat[i][j]));
        }
        printf("\n");
        k++;
    }
}


void del_mat(char **mat, size_t n) {
    if (n == 0) n = 3; //Для тестов

    for (size_t i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}


int get_sigma_diagonal(char **mat, size_t n) {
    size_t sigma = 0;
    for (size_t i = 0; i < n; i++) {
        sigma += (mat[i][i]);
    }
    return sigma;
}



