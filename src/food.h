#ifndef FOOD_H
#define FOOD_H

#include <GL/glut.h>
#include "utils.h"

#define ENERGY_PER_FOOD_UNIT 0.5

class Food {
    
private:
    float x;
    float y;
    float width;
    float height;
    int foodTimer;
    float energy_per_unit;

public:

    Food(float initialX, float initialY)
        : x(initialX), y(initialY), width(0.05f), height(0.05f), foodTimer(500) {
        // Constructor code if needed
        this->energy_per_unit = ENERGY_PER_FOOD_UNIT;
    }

    //Operator functions:
    // == 
    bool operator==(const Food& other) const {
        return (x == other.x && y == other.y &&
                width == other.width && height == other.height);
    }

    // Accessors gets
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    int getTimer() const {return foodTimer; }
    float getEnergyPerUnit() const { return energy_per_unit; }

    // Accessors sets
    void setPosition(float newX, float newY);
    void setTimer(int newT);

    //Other functions:
    void randPosition();

    void decreaseTimer();

    // Display the food with OpenGL
    void show_food() const ;
};

// Function to create a specified number of Food instances
void create_food_population(std::vector<Food>& foods, int food_qty);

#endif // FOOD_H