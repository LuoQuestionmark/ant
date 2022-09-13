#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_vect.h"

int true_value = 1;

vect_s * vect_init(double * array, int len) {
    vect_s* v = calloc(1, sizeof(vect_s));
    v->len = len;
    v->array = calloc(len, sizeof(double));
    for (int i=0; i < len; i++) {
        v->array[i] = array[i];
    }
    return v;
}

vect_s * vect_copy(vect_s const * v) {
    if (v == NULL) return NULL;
    vect_s* v2 = calloc(1, sizeof(vect_s));
    v2->len = v->len;
    v2->array = calloc(v2->len, sizeof(double));
    memcpy(v2->array, v->array, v->len * sizeof(double));
    return v2;
}

void vect_free(vect_s * v) {
    free(v->array);
    free(v);
}

double vect_dot_product(vect_s const * v1, vect_s const * v2, int * state) {
    if (v1->len != v2->len) {
        state = NULL;
        return 0;
    }

    double ans = 0;
    for (int i = 0; i < v1->len; i++) {
        ans += v1->array[i] * v2->array[i];
    }
    if (state != NULL) {
        state = &true_value;
    }
    return ans;
}

void vect_print(vect_s * v) {
    printf("vect: ");
    for (int i = 0; i < v->len; i++) {
        printf("%lf ", v->array[i]);
    }
}

mat_s * mat_init(vect_s ** vects, int size) {
    mat_s * m = calloc(1, sizeof(mat_s));
    m->size = size;
    m->vects = calloc(size, sizeof(vect_s *));
    for (int i = 0; i < size; i++) {
        m->vects[i] = vect_copy(vects[i]);
    }
    return m;
}
