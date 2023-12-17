// Host.h

#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include "utils.h"
#include <bits/stdc++.h>//used to manipulate vector
#include "meme.h"
#include "food.h"
#include "config.h"

using std::vector;

typedef enum HostStateEnum {
    LOOKING_FOR_FOOD, // Não há comida no campo de visao
    GOING_TO_FOOD, // Há comida no campo de visao
    EATING,
    TARGETING, // Coloca alvo em outro host
    TARGETED, // É alvo de um host
    ATTACKING, // Caso targeting e aggressiveness alto
    DEFENDING, // Caso targeted e aggressiveness alto
    FLEEING, // Caso targeted e aggressiveness baixo
    DEAD
} HostState;

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

typedef struct shape{
    float h;//hight
    float w;//width
}shape_t;

typedef struct gene{
    shape_t shape;
    RGB_t color;
    float fov; // field of view
}gene_t;

float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
    float size_lower_bound, float size_upper_bound, float size);
Host* create_initial_host();

class Host : public Meme {
private:
    // Keep track of the currently interacting food
    Food* currentFood;

    float mutate_color(float color_value);
    bool coin_toss();
    
public:
    HostState state;
    gene_t gene;
    position_t pos;

    position_t going_to;
    float energy;
    int random_movement_timer;

    Host(float initialAggressiveness, 
        float initialSpeed,
        gene_t initialGene,
        position_t initialPos) 
            : Meme(initialSpeed, initialAggressiveness), currentFood(nullptr) {
        // Constructor code for the Host class if needed

        this->energy = CONFIG["MAX_ENERGY"] / 2;
        this->change_position(initialPos.x, initialPos.y);
        this->change_color(initialGene.color.R, initialGene.color.G, initialGene.color.B);
        this->change_shape(initialGene.shape.h, initialGene.shape.w);
        /*speed = calculate_speed_based_on_size(CONFIG["SPEED_UPPER"], CONFIG["SPEED_LOWER"], 
            CONFIG["SHAPE_LOWER"], CONFIG["SHAPE_UPPER"], initialGene.shape.h);
        this->speed = speed;*/
        this->gene = initialGene;
        this->random_movement_timer = CONFIG["RANDOM_MOVEMENT_TIMER"];
        this->state = LOOKING_FOR_FOOD;
        //this->show_characteristics();
    }

    void change_position(float new_x, float new_y);
    void change_shape(float new_h, float new_w);
    void change_color(float new_R, float new_G, float new_B);

    //Show position, color and shape (terminal)
    void show_characteristics(void);
    //Display the host with openGL
    void show_energy_graphically(void);
    void show_fov_graphically(void);
    void show_aggression_graphically(void);
    void show_host(void);

    //Movement functions 
    void move_up(void);
    void move_right(void);
    void move_down(void);
    void move_left(void);

    //To change characteristics
    void update(std::vector<Food>& foods, int *number_of_living_hosts);
    void increase_energy(Food *food);
    float calculate_energy_loss();
    void decrease_energy(float subtracted_qtd);
    bool should_host_die(int *number_of_living_hosts);

    void mutate();

    //To perform actions
    bool eat(Food *food);
    bool findFoodInVision(std::vector<Food>& foods);
    void goTo(position_t position);
    void goToFood();
    bool hasFoundFood();
    void battle(Food *food);

    bool comparePositionsWithTolerance(position_t pos1, position_t pos2, float tolerance);
};

#endif
