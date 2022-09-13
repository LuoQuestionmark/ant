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

    vect_free(v1);
    vect_free(v2);
    mat_free(m);
    mat_free(m2);
    return 0;
}
