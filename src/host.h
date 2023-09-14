// Host.h

#ifndef HOST_H
#define HOST_H

#include "meme.h"

class Host : public Meme {
public:
    Host(unsigned char initialSpeed,
        unsigned char initialAggressiveness,unsigned char initialReproductionRate)

        : Meme(initialSpeed, initialAggressiveness, initialReproductionRate) {
        // Constructor code for the Host class if needed
    }

    void show_personality(void);

    // Host class members go here
};

#endif // HOST_H
