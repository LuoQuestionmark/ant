#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "my_vect.h"
#include "ant_tool.h"

int main() {
    srand(time(NULL));
    vect_s *v1, *v2;
    double d1[3] = {1, 2, 3.45};
    v1 = vect_init(d1, 3);
    double d2[3] = {2, 3.4, 1};
    v2 = vect_init(d2, 3);

    puts("create matrix:");
    vect_print(v1);
    puts("and");
    vect_print(v2);
    puts("gives");
    vect_s * vects[2] = {v1, v2};
    mat_s * m = mat_init(vects, 2);
    mat_print(m);
    puts("\n-----------\n");

    puts("create 2 * 3 zero matrix:");
    mat_s * m2 = mat_zeros(2, 3);
    mat_print(m2);
    puts("\n-----------\n");

    vect_s *v3, *v4, *v5;
    double d3[2] = {1, 8};
    double d4[2] = {-0.6, 2.9};
    double d5[2] = {7.32, 6.4};
    v3 = vect_init(d3, 2);
    v4 = vect_init(d4, 2);
    v5 = vect_init(d5, 2);
    vect_s * vects2[3] = {v3, v4, v5};
    mat_s * m3 = mat_init(vects2, 3);

    puts("mat");
    mat_print(m);
    puts("\ntimes mat");
    mat_print(m3);
    puts("\ngives");

    mat_s * m4 = mat_prod(m, m3);

    mat_print(m4);

    puts("\n-----------\n");

    puts("mat");
    mat_print(m3);
    puts("\ntimes mat");
    mat_print(m);
    puts("\ngives");

    mat_s * m5 = mat_prod(m3, m);

    mat_print(m5);
    puts("\n-----------\n");

    vect_free(v1);
    vect_free(v2);
    vect_free(v3);
    vect_free(v4);
    vect_free(v5);

    mat_free(m);
    mat_free(m2);
    mat_free(m3);
    mat_free(m4);
    mat_free(m5);
    return 0;
}
