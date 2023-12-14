#ifndef UTILS_H
#define UTILS_H

#include <random>//used to generate random numbers
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

float generate_random(float lower, float upper);
int generate_random_integer(int lower, int upper);
std::unordered_map<std::string, float> readConfig(const std::string& filename);

#endif // UTILS_H