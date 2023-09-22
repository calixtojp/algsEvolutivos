#ifndef MEME_H
#define MEME_H

class Meme {
public:

    Meme(float initialSpeed,
        float initialAggressiveness,
        float initialReproductionRate
        )
        :
        speed(initialSpeed),
        aggressiveness(initialAggressiveness),
        reproduction_rate(initialReproductionRate) {
        // Constructor code if needed
    }

    float speed;
    float aggressiveness;
    float reproduction_rate;

};

#endif // MYCLASS_H