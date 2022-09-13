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
