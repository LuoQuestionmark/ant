#ifndef ANT_TOOL
#define ANT_TOOL
#include "my_vect.h"

vect_s * mutation(vect_s const * src, double rate);
vect_s * crossover(vect_s const * v1, vect_s const * v2);
double evaluate(vect_s const * v);

typedef vect_s* population;

population* population_create(int size);
void population_free(population* p);
population* population_append();
population* population_select(population* src);

#endif
