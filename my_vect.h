#ifndef MYVECT
#define MYVECT

#include <stdbool.h>

struct _vect_s
{
    double* array;
    int len;
};
typedef struct _vect_s vect_s;

vect_s * vect_init(double * array, int len); 
vect_s * vect_zeros(int len);
vect_s * vect_copy(vect_s const * v);
void vect_free(vect_s * v);
double vect_dot_product(vect_s const * v1, vect_s const * v2, int * state);
double vect_norm2(vect_s const * v);
double vect_norminf(vect_s const * v);
vect_s * vect_sub(vect_s const * v1, vect_s const * v2, int * state);
void vect_print(vect_s * v);

struct mat
{
    // the vects should be saved line after line
    vect_s ** vects;
    int size;
};
typedef struct mat mat_s;

mat_s * mat_init(vect_s ** vects, int size);
mat_s * mat_init2(int row, int col, double * vars);
mat_s * mat_zeros(int row, int col);
mat_s * mat_add_row(mat_s * m, vect_s * v);
void mat_free(mat_s * m);
void mat_print(mat_s * m);

mat_s * mat_prod(mat_s const * m1, mat_s const * m2);
mat_s* mat_transpose(mat_s const * m);

#endif
