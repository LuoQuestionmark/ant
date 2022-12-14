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

    puts("vector product: \n");
    vect_print(v1);
    puts("\ntime to vector \n");
    vect_print(v2);
    printf("\nequal to %lf\n", vect_dot_product(v1, v2, NULL));
    puts("\n-----------\n\n");

    puts("mutation of vector: \n");
    vect_print(v1);
    puts("\nmutate to: ");
    vect_s * v1bis = mutation(v1, 1);
    vect_print(v1bis);
    puts("\n-----------\n\n");

    puts("crossover of vector: \n");
    vect_print(v1);
    puts("\ntimes to");
    vect_print(v2);
    puts("\ngive the result");
    vect_s * v3 = crossover(v1, v2);
    vect_print(v3);
    puts("\n-----------\n\n");

    puts("copy of vector: \n");
    vect_print(v1);
    puts("\ngive the result");
    vect_s * v4 = vect_copy(v1);
    vect_print(v4);
    puts("\n-----------\n\n");

    puts("vector zeros: \n");
    vect_s * v5 = vect_zeros(5);
    vect_print(v5);
    puts("\n-----------\n\n");

    vect_free(v1);
    vect_free(v1bis);
    vect_free(v2);
    vect_free(v3);
    vect_free(v4);
    vect_free(v5);

    return 0;
}
