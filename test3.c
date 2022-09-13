#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "my_vect.h"
#include "ant_tool.h"

int main() {
    srand(time(NULL));
    vect_s *v1 = generate_b(-1, -10, -100);

    puts("vector b with [-1 -10 -100]: \n");
    vect_print(v1);
    
    puts("\n-----------\n\n");

    vect_free(v1);

    return 0;
}
