#include "utils.h"

// Generate a random float
float generate_random(float lower, float upper) {
    // Initialize a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Use the Mersenne Twister engine
    std::uniform_real_distribution<float> distribution(lower, upper);

    // Generate and return a random float in the specified range
    return distribution(gen);
}

// Generate a random integer
int generate_random_integer(int lower, int upper) {
        // Initialize a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Use the Mersenne Twister engine
    std::uniform_int_distribution<int> distribution(lower, upper);

    // Generate and return a random int in the specified range
    return distribution(gen);
}

// Read the config file to get its parameters
std::unordered_map<std::string, float> readConfig(const std::string& filename) {
    std::unordered_map<std::string, float> config;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                config[key] = std::stof(value);
            }
        }
    }

    return config;
}