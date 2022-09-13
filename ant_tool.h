#ifndef ANT_TOOL
#define ANT_TOOL
#include "my_vect.h"

const int ANT_GENE_LENGTH;

vect_s * mutation(vect_s const * src, double rate);
vect_s * crossover(vect_s const * v1, vect_s const * v2);
double evaluate(vect_s const * v);

typedef mat_s population;

vect_s * generate_b(double arg1, double arg2, double arg3);
mat_s * generate_a(double arg1, double arg2, double arg3);

// population* population_create(int size);
// void population_free(population* p);
// population* population_append();
// population* population_select(population* src);

#endif
