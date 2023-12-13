#include "utils.h"

float generate_random(float lower, float upper) {
    // Initialize a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Use the Mersenne Twister engine
    std::uniform_real_distribution<float> distribution(lower, upper);

    // Generate and return a random float in the specified range
    return distribution(gen);
}

int generate_random_integer(int lower, int upper) {
        // Initialize a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Use the Mersenne Twister engine
    std::uniform_int_distribution<int> distribution(lower, upper);

    // Generate and return a random int in the specified range
    return distribution(gen);
}