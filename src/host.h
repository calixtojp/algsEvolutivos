// Host.h

#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include "utils.h"
#include <bits/stdc++.h>//used to manipulate vector
#include "meme.h"
#include "food.h"

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

class Host : public Meme {
private:

    position_t pos;
    RGB_t color;

    // Keep track of the currently interacting food
    Food* currentFood;

public:

    bool isEating;
    int eatingTimer;

    Host(float initialSpeed,
        float initialAggressiveness,
        float initialReproductionRate,
        float initialSize)

        : Meme(initialSpeed, initialAggressiveness, initialReproductionRate), currentFood(nullptr) {
        // Constructor code for the Host class if needed
    }

    void change_position(float new_x, float new_y);
    void change_size(float new_size);
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

};

void create_initial_population(vector<Host*>& Hosts, int hosts_qty);


#endif // HOST_H
