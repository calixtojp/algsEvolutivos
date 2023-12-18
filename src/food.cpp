#include "food.h"
#include "host.h"

// Create the initial food population
void create_food_population(std::vector<Food>& foods, int food_qty) {
    for (int i = 0; i < food_qty; ++i) {
        float pos_x = generate_random(-1, 1);
        float pos_y = generate_random(-1, 1);

        Food temp_food(pos_x, pos_y);
        foods.push_back(temp_food);
    }
}

// Set food position
void Food::setPosition(float newX, float newY) {
    this->x = newX;
    this->y = newY;
}

// Set food timer
void Food::setTimer(int newT){ foodTimer = newT; }

// Generate a random new position for food
void Food::randPosition(){
    x = generate_random(-1, 1);
    y = generate_random(-1, 1);
}

// Show food in the simulation
void Food::show_food() const {
    glColor3f(0.0f, 0.0f, 0.0f); // Standard black color
    glBegin(GL_POLYGON);

    glVertex2d(x - width / 2, y - height / 2);
    glVertex2d(x - width / 2, y + height / 2);
    glVertex2d(x + width / 2, y + height / 2);
    glVertex2d(x + width / 2, y - height / 2);

    glEnd();
}

// Decrease food timer
void Food::decreaseTimer(){ this->foodTimer--; }

// Update a food if its timer reaches 0
void Food::update() {
    if(this->getTimer() <= 0) {
        this->notifyTimerExpired();
        this->randPosition();
        this->setTimer(500);
    }
}

// Register a host in the vector of eatingHosts
void Food::registerHost(Host* host) {
    eatingHosts.push_back(host);
}

// Notify all hosts eating this food that its timer expired
void Food::notifyTimerExpired() {
    for (Host* host : eatingHosts) {
        host->state = LOOKING_FOR_FOOD;
    }
    eatingHosts.clear(); // Limpa o registro
}

// Check if eatingHosts vector is empty
bool Food::eatingHostsEmpty(){
    if(eatingHosts.size() == 0) return true;
    return false;
}

// Check size of eatingHosts vector
int Food::eatingHostsSize(){
    return eatingHosts.size();
}

// crossover of hosts' aggressiveness while they are eating the same food
void Food::contaminateHosts(Host *new_host){
    float chance, coin;

    for (Host* host : eatingHosts) {
        if(host->state == DEAD) continue;
        chance = host->energy / (host->energy + new_host->energy);
        coin = generate_random(0, 1.25);

        if(coin > 1){
            host->aggressiveness = (host->aggressiveness + new_host->aggressiveness)/2;
            new_host->aggressiveness = host->aggressiveness;
        } else if (coin > chance) {
            host->aggressiveness = new_host->aggressiveness;
        } else {
            new_host->aggressiveness = host->aggressiveness;
        }
    }
}
