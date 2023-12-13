// Host.h

#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include "utils.h"
#include <bits/stdc++.h>//used to manipulate vector
#include "meme.h"
#include "food.h"

#define MAX_ENERGY 100
#define ENERGY_LOSS_PER_TICK 0.25

#define SPEED_UPPER 0.05
#define SPEED_LOWER 0

#define AGGRESSIVENESS_UPPER 1
#define AGGRESSIVENESS_LOWER 0

#define REPRODUCTIONRATE_UPPER 1
#define REPRODUCTIONRATE_LOWER 0

#define POS_X_UPPER 1
#define POS_X_LOWER -1

#define POS_Y_UPPER 1
#define POS_Y_LOWER -1

#define SHAPE_UPPER 0.2
#define SHAPE_LOWER 0.1

#define MUTATION_MULTIPLICATIVE_MODIFIER 0.1f
#define MUTATION_ADDITIVE_MODIFIER 0.25f

using std::vector;

typedef struct position{
    float x;
    float y;
}position_t;

typedef struct RGB{
    float R;
    float G;
    float B;
}RGB_t;

typedef struct shape{
    float h;//hight
    float w;//width
}shape_t;

typedef struct gene{
    shape_t shape;
    RGB_t color;
}gene_t;

float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
    float size_lower_bound, float size_upper_bound, float size);
Host* create_initial_host();

class Host : public Meme {
private:
    // Keep track of the currently interacting food
    Food* currentFood;
    
    float fitness;

    float mutate_color(float color_value);
    bool coin_toss();
public:
    gene_t gene;
    position_t pos;

    bool isEating;
    int eatingTimer;
    bool is_alive;
    float energy;

    Host(float initialAggressiveness,
        float initialReproductionRate,
        gene_t initialGene,
        position_t initialPos) 
            : Meme(calculate_speed_based_on_size(SPEED_UPPER, SPEED_LOWER, 
            SHAPE_LOWER, SHAPE_UPPER, initialGene.shape.h), initialAggressiveness, 
            initialReproductionRate), currentFood(nullptr) {
        // Constructor code for the Host class if needed
        
        this->is_alive = true;
        this->energy = MAX_ENERGY / 2;
        this->change_position(initialPos.x, initialPos.y);
        this->change_color(initialGene.color.R, initialGene.color.G, initialGene.color.B);
        this->change_shape(initialGene.shape.h, initialGene.shape.w);
        speed = calculate_speed_based_on_size(SPEED_UPPER, SPEED_LOWER, 
            SHAPE_LOWER, SHAPE_UPPER, initialGene.shape.h);
        this->speed = speed;
        this->show_characteristics();
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

    void update(std::vector<Food>& foods, int *number_of_living_hosts);
    void increase_energy(Food *food);
    void decrease_energy();
    void kill_host_if_energy_is_zero(int *number_of_living_hosts);

    void mutate();
};

#endif
