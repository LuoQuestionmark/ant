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

    printf("vector ");
    vect_print(v1);
    printf(" time to vector ");
    vect_print(v2);
    printf("equal to %lf\n", vect_dot_product(v1, v2, NULL));

    printf("mutation of vector: ");
    vect_print(v1);
    printf(" :");
    vect_s * v1bis = mutation(v1, 1);
    vect_print(v1bis);
    puts("");

    vect_free(v1);
    vect_free(v1bis);
    vect_free(v2);

    return 0;
}
