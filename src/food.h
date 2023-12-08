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

public:
    Food(float initialX, float initialY)
        : x(initialX), y(initialY), width(0.05f), height(0.05f) {
        // Constructor code if needed
    }

    // Accessors
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Setters
    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
    }

    // Display the food with OpenGL
    void show_food() const {
        glColor3f(0.0f, 0.0f, 0.0f); // Standard black color
        glBegin(GL_POLYGON);

        glVertex2d(x - width / 2, y - height / 2);
        glVertex2d(x - width / 2, y + height / 2);
        glVertex2d(x + width / 2, y + height / 2);
        glVertex2d(x + width / 2, y - height / 2);

        glEnd();
    }

    // Equality operator for comparing two Food objects
    bool operator==(const Food& other) const {
        return (x == other.x && y == other.y &&
                width == other.width && height == other.height);
    }
};

// Function to create a specified number of Food instances
void create_food_population(std::vector<Food>& foods, int food_qty);

#endif // FOOD_H