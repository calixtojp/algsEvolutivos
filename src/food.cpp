#include "food.h"
#include "host.h"

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

void Food::decreaseTimer(){ this->foodTimer--; }

void Food::update() {
    if(this->getTimer() <= 0) {
        this->notifyTimerExpired();
        this->randPosition();
        this->setTimer(500);
    }
}

void Food::registerHost(Host* host) {
    eatingHosts.push_back(host);
}

void Food::notifyTimerExpired() {
    for (Host* host : eatingHosts) {
        host->isEating = false;
    }
    eatingHosts.clear(); // Limpa o registro
}

void Food::contaminateHosts(Host *new_host){
    float chance, coin;
    
    for (Host* host : eatingHosts) {
        chance = host->energy / (host->energy + new_host->energy);
        coin = generate_random(0, 1);

        // Seg_fault here, corrupted double linked list
        /*if (coin > chance) {
            host->aggressiveness = new_host->aggressiveness;
        } else {
            new_host->aggressiveness = host->aggressiveness;
        }*/
    }
}