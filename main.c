//Copyright 2019 EvilBorsch"
#include "libdynamic.h"
#include <assert.h>
#include "libstatic.h"
#include <stdio.h>
#include <string.h>


/*
 * В вашем распоряжении — нижняя треугольная матрица, полученная из воображаемой квадратной матрицы размером 100 000 x 100 000
 * и заполненная значениями от 0 до 3. Предложите эффективную организацию ее хранения в памяти,
 * инициализируйте матрицу и найдите сумму последних элементов в каждой ее строке (элементов диагонали)
 * с помощью последовательного и параллельного с использованием нескольких процессов алгоритмов
 * с учётом оптимизации работы с кэш-памятью.

 */


void test();


int main() {
    test();

    return 0;
}


void test() {
    {
        int n = 100;
        char **mat = init_with_num(n, 2);
        size_t k = 0;
        for (size_t i = 0 ; i < n ; i++) {
            for (size_t j = 0 ; j <= k ; j++) {
                assert(2 == (mat[i][j]));
            }
            k++;
        }
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

    {
        int n = 3;
        char **mat = init_with_num(n, 1);
        mat[0][0] = (1);
        mat[1][1] = (2);
        mat[2][2] = (3);
        assert(get_sigma_diagonal(mat, n) == 6);
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

    {
        int n = 3;
        char **mat = init_with_num(n, 1);
        assert(get_sigma_diagonal(mat, n) == 3);
        del_mat(mat, n);
        printf("%s\n", "OK");
    }


    {

        int n = 5;
        char **mat = init_with_num(n, 3);
        assert(get_sigma_diagonal(mat, n) == summa_diagonali(4,mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

    {
        int n = 100;
        char **mat = init_with_num(n, 1);
        assert(100 == summa_diagonali(4,mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");
    }


    {

        int n = 100;
        char **mat = init_with_num(n, 1);
        assert(get_sigma_diagonal(mat, n) == summa_diagonali(4,mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

    {
        int n = 30000;
        char **mat = init_with_num(n, 1);
        assert(summa_diagonali(4,mat, n) ==30000);
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

}
