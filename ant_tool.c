#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ant_tool.h"

static double randn()
{
    double a = (double)rand() / (double)RAND_MAX;
    double b = (double)rand() / (double)RAND_MAX;
    return sqrt(-2 * log2l(a)) * cos(2 * 3.14159 * b);
}

vect_s *mutation(vect_s const *src, double rate)
{
    vect_s *new = calloc(1, sizeof(vect_s));
    new->len = src->len;
    new->array = calloc(src->len, sizeof(double));

    for (int i = 0; i < new->len; i++)
    {
        new->array[i] = src->array[i] + rate * randn();
    }
    return new;
}

vect_s *crossover(vect_s const *v1, vect_s const *v2)
{
    /*  cross the first one onto the second one,
     * because of the limit of c language, to get
     * both of the result, call crossover(v2, v1) later
     *
     * return NULL if the operation is not legal
     */
    if (v1->len != v2->len)
        return NULL;

    vect_s *ret = calloc(1, sizeof(vect_s));
    ret->len = v1->len;
    ret->array = calloc(ret->len, sizeof(double));
    int sep_index = (int)((double)rand() / (double)RAND_MAX * ret->len);
    for (int i = 0; i < sep_index; i++)
    {
        ret->array[i] = v1->array[i];
    }
    for (int i = sep_index; i < v1->len; i++)
    {
        ret->array[i] = v2->array[i];
    }
    return ret;
}

vect_s * generate_b(double arg1, double arg2, double arg3) {
    vect_s * b = vect_zeros(24 + 4 * 8);
    for (int i = 12; i < 12 + 16; i += 4) {
        b->array[i] = 1;
        b->array[i+1] = -arg1 - arg2 - arg3;
        b->array[i+2] = arg1 * arg2 + arg2 * arg3 + arg1 * arg3;
        b->array[i+3] = -arg1 * arg2 * arg3;
    }
    return b;
}

mat_s * generate_a(double arg1, double arg2, double arg3) {
    mat_s * ma = mat_zeros(28, 17);
    // fill A_e
    for (int i = 0; i < 4; i++) {
        ma->vects[i*3 + 0]->array[i*3 + 0] = 1;
        ma->vects[i*3 + 0]->array[i*3 + 1] = 1;
        ma->vects[i*3 + 0]->array[i*3 + 2] = 1;
        ma->vects[i*3 + 1]->array[i*3 + 0] = -(arg1 * arg2);
        ma->vects[i*3 + 1]->array[i*3 + 1] = -(arg1 * arg3);
        ma->vects[i*3 + 1]->array[i*3 + 2] = -(arg2 * arg3);
        ma->vects[i*3 + 2]->array[i*3 + 0] = arg2 * arg3;
        ma->vects[i*3 + 2]->array[i*3 + 1] = arg1 * arg3;
        ma->vects[i*3 + 2]->array[i*3 + 2] = arg1 * arg3;
    }

    // fill A_1
    ma->vects[0]->array[12] = -1;
    ma->vects[0]->array[14] = +1;
    ma->vects[1]->array[12] = -1;
    ma->vects[1]->array[13] = -1;
    ma->vects[1]->array[15] = +1;
    ma->vects[2]->array[13] = -1;
    ma->vects[2]->array[16] = +1;

    // fill A_2
    ma->vects[3]->array[12] = -1;
    ma->vects[3]->array[14] = -1;
    ma->vects[4]->array[12] = -2;
    ma->vects[4]->array[13] = -1;
    ma->vects[4]->array[15] = -1;
    ma->vects[5]->array[13] = -2;
    ma->vects[5]->array[16] = -1;

    // fill A_3
    ma->vects[6]->array[12] = -1;
    ma->vects[6]->array[14] = +1;
    ma->vects[7]->array[12] = -2;
    ma->vects[7]->array[13] = -1;
    ma->vects[7]->array[15] = +1;
    ma->vects[8]->array[13] = -2;
    ma->vects[8]->array[16] = +1;

    // fill A_4
    ma->vects[9]->array[12] = -1;
    ma->vects[9]->array[14] = -1;
    ma->vects[10]->array[12] = -1;
    ma->vects[10]->array[13] = -1;
    ma->vects[10]->array[15] = -1;
    ma->vects[11]->array[13] = -1;
    ma->vects[11]->array[16] = -1;

    // fill A_5
    for (int i = 12; i < 12 + 4 * 4; i += 4) {
        ma->vects[i + 0]->array[14] = 2;
        ma->vects[i + 1]->array[14] = 1;
        ma->vects[i + 1]->array[15] = 2;
        ma->vects[i + 2]->array[15] = 1;
        ma->vects[i + 2]->array[16] = 2;
        ma->vects[i + 3]->array[16] = 1;
    }
    return ma;
}

double evaluate(vect_s const* v) {
    if (v->len != 3 + 17) {
        printf("wrong input size of vector at line %d in evaluate function", __LINE__);
        exit(1);
    }
    double arg1, arg2, arg3;
    arg1 = v->array[0];
    arg2 = v->array[1];
    arg3 = v->array[2];

    mat_s*  mat_a = generate_a(arg1, arg2, arg3);
    vect_s* vec_b = generate_b(arg1, arg2, arg3);

    mat_s* mat_X = mat_zeros(v->len - 3, 1);
    for (int i = 3; i < v->len; i++) {
        mat_X->vects[i - 3]->array[0] = v->array[i];
    }


    mat_s* mat_result = mat_prod(mat_a, mat_X);
    vect_s* vect_result = mat_result->vects[0]; // don't free this!
    vect_s* diff = vect_sub(vect_result, vec_b, NULL);
    double val = vect_norm2(diff) / vect_norm2(vec_b) + 0.01 * vect_norminf(diff) / vect_norminf(vec_b);

    mat_free(mat_a);
    vect_free(vec_b);
    mat_free(mat_X);
    mat_free(mat_result);
    vect_free(diff);

    return val;
}
