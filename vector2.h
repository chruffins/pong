#ifndef VECTOR2_H
#define VECTOR2_H
#include<stdlib.h>
#include<math.h>

struct vector2_t {
    float x;
    float y;
} typedef vector2;

vector2* vector2_create(float x, float y);
void vector2_destroy(vector2* vec);
void vector2_addf(vector2*, float, float);
vector2 vector2_addv2(vector2*, vector2*);
void vector2_iaddv2(vector2*, vector2*);
void vector2_smult(vector2* v, float f);

float vector2_magnitude(vector2* vec);
float vector2_unit(vector2* vec);

#endif