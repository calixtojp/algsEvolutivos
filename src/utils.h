#ifndef UTILS_H
#define UTILS_H

#include <random>//used to generate random numbers

typedef struct position{
    float x;
    float y;
}position_t;

typedef struct RGB{
    float R;
    float G;
    float B;
}RGB_t;

float generate_random(float lower, float upper);

#endif // UTILS_H