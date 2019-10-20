#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../libstatic.h"


digit int_to_digit(int chis) {
    digit temp;

    temp.bitdig1 = (char) ((chis / 2) % 2);
    temp.bitdig2 = (char) (chis % 2);
    return temp;
}


digit **init_matrix_from_keyboard(size_t n) {

    digit **mat = (digit **) malloc(n * sizeof(digit *));
    assert(mat != NULL);
    size_t k = 0;

    for (size_t i = 0; i < n; i++) {
        mat[i] = (digit *) malloc(sizeof(digit) * (k + 1));
        assert(mat[i] != NULL);
        for (size_t j = 0; j <= k; j++) {
            int chis;
            scanf("%d", &chis);
            mat[i][j] = int_to_digit(chis);
        }
        k++;
    }
    return mat;
}


digit **init_with_num(size_t n, int num) {
    digit t = int_to_digit(num);

    digit **mat = (digit **) malloc(n * sizeof(digit *));
    assert(mat != NULL);
    size_t k = 0;
    for (size_t i = 0; i < n; i++) {
        mat[i] = (digit *) malloc(sizeof(digit) * (k + 1));
        assert(mat[i] != NULL);
        for (size_t j = 0; j <= k; j++) {
            mat[i][j] = t;
        }
        k++;
    }
    return mat;
}


void print_mat(digit **mat, size_t n) {
    size_t k = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j <= k; j++) {
            printf("%d ", digit_to_int(mat[i][j]));
        }
        printf("\n");
        k++;
    }
}


int digit_to_int(digit d) {
    return abs(d.bitdig1) * 2 + abs(d.bitdig2);
}


void del_mat(digit **mat, size_t n) {
    if (n == 0) n = 3; //Для тестов

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}


int get_sigma_diagonal(digit **mat, size_t n) {
    size_t sigma = 0;
    for (size_t i = 0; i < n; i++) {
        sigma += digit_to_int(mat[i][i]);
    }
    return sigma;
}



