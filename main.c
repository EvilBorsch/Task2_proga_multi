#include <stdio.h>
#include "libstatic.h"
#include <assert.h>


void test() {
    {
        int n = 100;
        digit **mat = init_with_num(n, 2);
        size_t k = 0;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j <= k; j++) {
                assert(2 == digit_to_int(mat[i][j]));
            }
            k++;
        }
        del_mat(mat, n);
        printf("%s\n", "OK");
    }

    {
        int n = 3;
        digit **mat = init_with_num(n, 1);
        mat[0][0] = int_to_digit(1);
        mat[1][1] = int_to_digit(2);
        mat[2][2] = int_to_digit(3);
        assert(get_sigma_diagonal(mat, n) == 6);
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


    {
        int n = 3;
        digit **mat = init_with_num(n, 1);
        assert(get_sigma_diagonal(mat, n) == 3);
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


}


int main() {
    test();

}
