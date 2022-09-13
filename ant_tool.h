#ifndef ANT_TOOL
#define ANT_TOOL
#include "my_vect.h"

const int ANT_GENE_LENGTH;

vect_s * mutation(vect_s const * src, double rate);
vect_s * crossover(vect_s const * v1, vect_s const * v2);
double evaluate(vect_s const * v);



// typedef vect_s* population;
// not sure if needed
// population* population_create(int size);
// void population_free(population* p);
// population* population_append();
// population* population_select(population* src);

#endif
