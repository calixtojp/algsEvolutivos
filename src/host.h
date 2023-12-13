// Host.h

#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include "utils.h"
#include <bits/stdc++.h>//used to manipulate vector
#include "meme.h"
#include "food.h"

#define MAX_ENERGY 100
#define ENERGY_LOSS_PER_TICK 0.1

#define SPEED_UPPER 0.05
#define SPEED_LOWER 0

#define AGGRESSIVENESS_UPPER 1
#define AGGRESSIVENESs_LOWER 0

#define REPRODUCTIONRATE_UPPER 1
#define REPRODUCTIONRATE_LOWER 0

#define POS_X_UPPER 1
#define POS_X_LOWER -1

#define POS_Y_UPPER 1
#define POS_Y_LOWER -1

#define SHAPE_UPPER 0.2
#define SHAPE_LOWER 0.1

using std::vector;

typedef struct shape{
    float h;//hight
    float w;//width
}shape_t;



class Host : public Meme {
private:

    position_t pos;
    shape_t shape;
    RGB_t color;

    // Keep track of the currently interacting food
    Food* currentFood;
    float energy;

public:

    bool isEating;
    int eatingTimer;
    bool is_alive;

    Host(float initialSpeed,
        float initialAggressiveness,
        float initialReproductionRate)

        : Meme(initialSpeed, initialAggressiveness, initialReproductionRate), currentFood(nullptr) {
        // Constructor code for the Host class if needed
        this->is_alive = true;
        this->energy = MAX_ENERGY / 2;
    }

    void change_position(float new_x, float new_y);
    void change_shape(float new_h, float new_w);
    void change_color(float new_R, float new_G, float new_B);

    //Show position, color and shape (terminal)
    void show_characteristics(void);
    //Display the host with openGL
    void show_host(void);

    //Movement functions 
    void move_up(void);
    void move_right(void);
    void move_down(void);
    void move_left(void);

    //Handling food interactions
    void interact_with_food(std::vector<Food>& foods);

    void update(std::vector<Food>& foods);
    void increase_energy(Food *food);
    void decrease_energy();
    void kill_host_if_energy_is_zero();
};

float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
    float size_lower_bound, float size_upper_bound, float size);
void create_initial_population(vector <Host*> &Hostes, int hostes_qtd);


#endif
