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
    printf("[ ");
    for (int i = 0; i < v->len; i++) {
        printf("%lf ", v->array[i]);
    }
    printf("]");
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

mat_s * mat_add_row(mat_s * m, vect_s * v) {
    if (m->vects == NULL || m->vects[0] == NULL) {
        return NULL;
    }
    if (m->vects[0]->len != v->len) return NULL;

    m->size += 1;
    vect_s ** tmp = calloc(m->size, sizeof(vect_s *));
    memcpy(tmp, m->vects, (m->size-1) * sizeof(vect_s *));
    free(m->vects);
    m->vects = tmp;
    m->vects[m->size-1] = v;
    return m;
}

mat_s * mat_zeros(int row, int col) {
    if (row <= 0 || col <= 0) return NULL;
    vect_s * vz = calloc(col, sizeof(double));
    mat_s * m = calloc(1, sizeof(mat_s));
    m->vects = calloc(row, sizeof(vect_s*));
    for (int i = 0; i < row; i++) {
        m->vects[i] = vect_copy(vz);
    }
    vect_free(vz);
    return m;
}

void mat_print(mat_s * m){
    for (int i = 0; i < m->size - 1; i++) {
        if (i == 0) printf("[ ");
        else printf("  ");
        vect_print(m->vects[i]);
        puts("");
    }
    printf("  ");
    vect_print(m->vects[m->size - 1]);
    printf(" ]");
}

void mat_free(mat_s * m) {
    for (int i = 0; i < m->size; i++) {
        vect_free(m->vects[i]);
    }
    free(m->vects);
    free(m);
}

mat_s * mat_prod(mat_s const * m1, mat_s const * m2) {
    if (m1->vects == NULL || m1->vects[0] == NULL) {
        return NULL;
    }
    if (m2->vects == NULL || m2->vects[0] == NULL) {
        return NULL;
    }
    if (m1->vects[0]->len != m2->size) return NULL;

    // TODO: not finish!
    return NULL;
}
