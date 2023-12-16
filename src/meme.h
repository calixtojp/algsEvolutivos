#ifndef MEME_H
#define MEME_H

#include "utils.h"

class Meme {
public:

    Meme(float initialSpeed,
        float initialAggressiveness
        )
        :
        speed(initialSpeed),
        aggressiveness(initialAggressiveness) {
        // Constructor code if needed
    }

    float speed;
    float aggressiveness;

};

#endif