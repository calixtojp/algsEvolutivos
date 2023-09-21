// Host.h

#ifndef HOST_H
#define HOST_H

#include <stdio.h>
#include "meme.h"

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

class Host : public Meme {
private:

    position_t pos;
    shape_t shape;
    RGB_t color;

public:

    Host(float initialSpeed,
        unsigned char initialAggressiveness,
        unsigned char initialReproductionRate)

        : Meme(initialSpeed, initialAggressiveness, initialReproductionRate) {
        // Constructor code for the Host class if needed
    }

    void change_position(float new_x, float new_y);
    void change_shape(float new_h, float new_w);
    void chage_color(float new_R, float new_G, float new_B);

    void show_characteristics(void);
    void show_host(void);

    void move_up(void);
    void move_right(void);
    void move_down(void);
    void move_left(void);

};

#endif // HOST_H
