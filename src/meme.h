#ifndef MEME_H
#define MEME_H

class Meme {
public:

    Meme(float initialSpeed,
        float initialAggressiveness,
        float initialReproductionRate,
        float initialSize
        )
        :
        speed(initialSpeed),
        aggressiveness(initialAggressiveness),
        reproduction_rate(initialReproductionRate),
        size(initialSize){
        // Constructor code if needed
    }

    float energy;
    float speed;
    float aggressiveness;
    float reproduction_rate;
    float size;

};

#endif