#ifndef FOOD_H
#define FOOD_H

#include <GL/glut.h>
#include "utils.h"

class Food {
private:
    float x;
    float y;
    float width;
    float height;
    int foodTimer;

public:

    Food(float initialX, float initialY)
        : x(initialX), y(initialY), width(0.05f), height(0.05f), foodTimer(500) {
        // Constructor code if needed
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