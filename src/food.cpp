#include "food.h"

void create_food_population(std::vector<Food>& foods, int food_qty) {
    for (int i = 0; i < food_qty; ++i) {
        float pos_x = generate_random(-1, 1);
        float pos_y = generate_random(-1, 1);

        Food temp_food(pos_x, pos_y);
        foods.push_back(temp_food);
    }
}

void Food::setPosition(float newX, float newY) {
    this->x = newX;
    this->y = newY;
}

void Food::setTimer(int newT){ foodTimer = newT; }

void Food::randPosition(){
    x = generate_random(-1, 1);
    y = generate_random(-1, 1);
}

void Food::show_food() const {
    glColor3f(0.0f, 0.0f, 0.0f); // Standard black color
    glBegin(GL_POLYGON);

    glVertex2d(x - width / 2, y - height / 2);
    glVertex2d(x - width / 2, y + height / 2);
    glVertex2d(x + width / 2, y + height / 2);
    glVertex2d(x + width / 2, y - height / 2);

    glEnd();
}

void Food::decreaseTimer(){ foodTimer--; }