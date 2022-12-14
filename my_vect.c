#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_vect.h"

const int true_value = 1;
const int false_value = 0;

vect_s * vect_init(double * array, int len) {
    vect_s* v = calloc(1, sizeof(vect_s));
    v->len = len;
    v->array = calloc(len, sizeof(double));
    for (int i=0; i < len; i++) {
        v->array[i] = array[i];
    }
    return v;
}

vect_s * vect_zeros(int len) {
    vect_s* v = calloc(1, sizeof(vect_s));
    v->len = len;
    v->array = calloc(len, sizeof(double));
    memset(v->array, 0, sizeof(double) * len);
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

double vect_norm2(vect_s const * v) {
    double sum = 0;
    for (int i = 0; i < v->len; i++) {
        sum += v->array[i] * v->array[i];
    }

    return sqrt(sum);
}

double vect_norminf(vect_s const * v) {
    double val = 0;
    for (int i = 0; i < v->len; i++) {
        int tmp = fabs(v->array[i]);
        if (tmp > val) {
            val = tmp;
        }
    }
    return val;
}

vect_s * vect_sub(vect_s const * v1, vect_s const * v2, int * state) {
    if (v1->len != v2->len) {
        if (state != NULL) {
            state = &false_value;
        }
        return NULL;
    }

    vect_s* ans = vect_copy(v1);
    for (int i = 0; i < v1->len; i++) {
        ans->array[i] -= v2->array[i];
    }

    if (state != NULL) {
        state = &true_value;
    }
    return ans;
}

void vect_print(vect_s * v) {
    printf("[ ");
    for (int i = 0; i < v->len; i++) {
        printf("%f ", v->array[i]);
    }
    printf("]");
    fflush(stdout);
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

mat_s * mat_init2(int row, int col, double * vars) {
    if (vars == NULL) return NULL;
    mat_s * m = mat_zeros(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int dep = i * col + j;
            double var = vars[dep];
            m->vects[i]->array[j] = var;
        }
    }
    return m;
}

mat_s * mat_zeros(int row, int col) {
    if (row <= 0 || col <= 0) return NULL;
    vect_s * vz = calloc(1, sizeof(vect_s));
    vz->len = col;
    vz->array = calloc(col, sizeof(double));
    mat_s * m = calloc(1, sizeof(mat_s));
    m->size = row;
    m->vects = calloc(row, sizeof(vect_s*));
    for (int i = 0; i < row; i++) {
        m->vects[i] = vect_copy(vz);
    }
    vect_free(vz);
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

void mat_print(mat_s * m){
    if (m->size == 0) return;
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

mat_s* mat_transpose(mat_s const * m) {
    if (m == NULL || m->vects == NULL || m->vects[0] == NULL) {
        puts("invalid argument in mat transpose");
        exit(1);
    }
    int origin_h = m->size;
    int origin_w = m->vects[0]->len;

    mat_s* out = mat_zeros(origin_w, origin_h);

    for (int i = 0; i < origin_h; i++) {
        for (int j = 0; j < origin_w; j++) {
            out->vects[j]->array[i] = m->vects[i]->array[j];
        }
    }

    return out;
}

mat_s * mat_prod(mat_s const * m1, mat_s const * m2) {
    if (m1->vects == NULL || m1->vects[0] == NULL) {
        return NULL;
    }
    if (m2->vects == NULL || m2->vects[0] == NULL) {
        return NULL;
    }
    if (m1->vects[0]->len != m2->size) return NULL;

    mat_s * m3 = mat_zeros(m1->size, m2->vects[0]->len);
    for (int i = 0; i < m1->size; i++) {
        for (int j = 0; j < m2->vects[0]->len; j++) {
            int local_sum = 0;
            for (int k = 0; k < m2->size; k++) {
                local_sum += m1->vects[i]->array[k] * m2->vects[k]->array[j];
            }
            m3->vects[i]->array[j] = local_sum; // SUM
        }
    }
    return m3;
}
