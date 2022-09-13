#ifndef MYVECT
#define MYVECT

struct _vect_s
{
    double* array;
    int len;
};
typedef struct _vect_s vect_s;

vect_s * vect_init(double * array, int len); 
void vect_free(vect_s * v);

double vect_dot_product(vect_s const * v1, vect_s const * v2, int * state);

void vect_print(vect_s * v);

#endif
