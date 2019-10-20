//
// Created by Дмитрий Гуляченков on 20.10.2019.
//

#ifndef ZADANIE_2_MULTITHREAD_PROGA_MAIN_H
#define ZADANIE_2_MULTITHREAD_PROGA_MAIN_H

#endif //ZADANIE_2_MULTITHREAD_PROGA_MAIN_H


typedef struct {
    char bitdig1:1;
    char bitdig2:1;
} digit;


digit int_to_digit(int chis);

digit **init_matrix_from_keyboard(size_t n);

digit **init_with_num(size_t n, int num);

void print_mat(digit **mat, size_t n);

int digit_to_int(digit d);

void del_mat(digit **mat, size_t n);

int get_sigma_diagonal(digit **mat, size_t n);


