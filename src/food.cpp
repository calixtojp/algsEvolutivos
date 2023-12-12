#include "food.h"

void create_food_population(std::vector<Food>& foods, int food_qty) {
    for (int i = 0; i < food_qty; ++i) {
        float pos_x = generate_random(-1, 1);
        float pos_y = generate_random(-1, 1);

        Food temp_food(pos_x, pos_y);
        foods.push_back(temp_food);
    }
}