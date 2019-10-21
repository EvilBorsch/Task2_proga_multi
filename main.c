#include <stdio.h>
#include "libstatic.h"
#include <assert.h>
#include "libdynamic.h"



void test() {
    {
        int n = 100;
        char **mat = init_with_num(n, 2);
        size_t k = 0;
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j <= k; j++) {
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
        int n = 100;
        char **mat = init_with_num(n, 1);
        assert(100 == find_sigma_diagonals(mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


    {

        int n = 5;
        char **mat = init_with_num(n, 3);
        assert(get_sigma_diagonal(mat, n) == find_sigma_diagonals(mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


    {

        int n = 100;
        char **mat = init_with_num(n, 1);

        assert(get_sigma_diagonal(mat, n) == find_sigma_diagonals(mat, n));
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


    {
        int n = 30000;
        char **mat = init_with_num(n, 1);
        assert(find_sigma_diagonals(mat, n) > 1);
        del_mat(mat, n);
        printf("%s\n", "OK");

    }


}


int main() {


    test();

    return 0;

}





