#include "vector2.h"

vector2* vector2_create(float x, float y) {
    vector2* n_vector = (vector2*)malloc(sizeof(vector2));
    n_vector->x = x;
    n_vector->y = y;

    return n_vector;
}

void vector2_destroy(vector2* vec) {
    free(vec);
}

void vector2_addf(vector2* vec, float x, float y) {
    vec->x += x;
    vec->y += y;
}

vector2 vector2_addv2(vector2* v1, vector2* v2) {
    vector2 result;

    result.x = v1->x + v2->x;
    result.y = v1->y + v2->y;
    return result;
}

void vector2_smult(vector2* v, float f) {
    v->x *= f;
    v->y *= f;
}

void vector2_iaddv2(vector2* v1, vector2* v2) {
    v1->x += v2->x;
    v1->y += v2->y;
}

float vector2_magnitude(vector2* vec) {
    return (vec->x * vec->x) + (vec->y * vec->y);
}

float vector2_unit(vector2* vec) {
    return sqrt(vector2_magnitude(vec));
}