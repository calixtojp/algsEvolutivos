#ifndef MEME_H
#define MEME_H

class Meme {
public:

    Meme(float initialSpeed,
        unsigned char initialAggressiveness,
        unsigned char initialReproductionRate
        )
        :
        speed(initialSpeed),
        aggressiveness(initialAggressiveness),
        reproduction_rate(initialReproductionRate) {
        // Constructor code if needed
    }

    float speed;
    unsigned char aggressiveness;
    unsigned char reproduction_rate;

};

#endif // MYCLASS_H