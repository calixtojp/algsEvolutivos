#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "host.h"

int seed = 0;

// Changes host position
void Host::change_position(float new_x, float new_y){
    this->pos.x = new_x;
    this->pos.y = new_y;
}

// Changes host shape
void Host::change_shape(float new_h, float new_w){
    this->gene.shape.h = new_h;
    this->gene.shape.w = new_w;
}

// Changes host color
void Host::change_color(float new_R, float new_G, float new_B){
    this->gene.color.R = new_R;
    this->gene.color.G = new_G;
    this->gene.color.B = new_B;
}

// Show host characteristics
void Host::show_characteristics(){
    printf("x:%.2f | y:%.2f | h:%.3f | w:%.3f | RGB(%.2f,%.2f,%.2f) | speed:%.3f | fov:%.3f | agr:%.3f\n",
        this->pos.x,
        this->pos.y,
        this->gene.shape.h,
        this->gene.shape.w,
        this->gene.color.R,
        this->gene.color.G,
        this->gene.color.B,
        this->speed,
        this->gene.fov,
        this->aggressiveness
    );
}

// Show energy bar in the simulation
void Host::show_energy_graphically(void){
    glColor3f(0, 0, 1);//Energy will be blue
    glBegin(GL_POLYGON);// Tells OpenGL that the next points will be used to draw a polygon

    float energy_ratio = this->energy / CONFIG["MAX_ENERGY"];

    // Added each vertex of the rectangle:
    //Bottom left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y-this->gene.shape.h/2);
    //Upper left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y-this->gene.shape.h/4);
    //Upper right:
    glVertex2d(this->pos.x-this->gene.shape.w/2 + this->gene.shape.w*energy_ratio, this->pos.y-this->gene.shape.h/4);
    //Bottom right:
    glVertex2d(this->pos.x-this->gene.shape.w/2 + this->gene.shape.w*energy_ratio, this->pos.y-this->gene.shape.h/2);

    glEnd();// Tell OpenGL that it has finished sending the polygon vertices
}

// Show field of view in the simulation
void Host::show_fov_graphically(void){

    // glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0); // Define perimeter's color (black in this case)

    glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP to draw the perimeter
    glVertex2f(this->pos.x-this->gene.fov, this->pos.y-this->gene.fov); // Bottom left vertex
    glVertex2f(this->pos.x+this->gene.fov, this->pos.y-this->gene.fov);  // Bottom right vertex
    glVertex2f(this->pos.x+this->gene.fov, this->pos.y+this->gene.fov);   // Upper right vertex
    glVertex2f(this->pos.x-this->gene.fov, this->pos.y+this->gene.fov);  // Upper left vertex
    glEnd();

    // glFlush();
}

// Show aggression bar in the simulation
void Host::show_aggression_graphically(void){
    glColor3f(1, 0, 0);//Aggression will be blue
    glBegin(GL_POLYGON);// Tells OpenGL that the next points will be used to draw a polygon

    float agress_ratio = this->aggressiveness / CONFIG["AGGRESSIVENESS_TRESHHOLD"];

    // Added each vertex of the rectangle:
    //Bottom left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y+this->gene.shape.h/4);
    //Upper left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y+this->gene.shape.h/2);
    //Upper right:
    glVertex2d(this->pos.x-this->gene.shape.w/2 + this->gene.shape.w*agress_ratio, this->pos.y+this->gene.shape.h/2);
    //Bottom right:
    glVertex2d(this->pos.x-this->gene.shape.w/2 + this->gene.shape.w*agress_ratio, this->pos.y+this->gene.shape.h/4);

    glEnd();// Tell OpenGL that it has finished sending the polygon vertices
}

// Show host in the simulation
void Host::show_host(void){
    // Will draw a polygon with 4 vertices

    glColor3f(this->gene.color.R, this->gene.color.G, this->gene.color.B);
    glBegin(GL_POLYGON);// Tells OpenGL that the next points will be used to draw a polygon

    // Added each vertex of the rectangle:
    //Bottom left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y-this->gene.shape.h/2);
    //Upper left:
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y+this->gene.shape.h/2);
    //Upper right:
    glVertex2d(this->pos.x+this->gene.shape.w/2, this->pos.y+this->gene.shape.h/2);
    //Bottom right:
    glVertex2d(this->pos.x+this->gene.shape.w/2, this->pos.y-this->gene.shape.h/2);

    glEnd();// Tell OpenGL that it has finished sending the polygon vertices

    this->show_energy_graphically();

    this->show_fov_graphically();

    this->show_aggression_graphically();
}

// Move the host to the positon above itself
void Host::move_up(void){
    this->pos.y += this->speed;
    if(this->pos.y > 1){
        this->pos.y = -1;
        this->pos.x = generate_random(-1, 1);
    }
}

// Move the host to the positon on the right side of itself
void Host::move_right(void){
    this->pos.x += this->speed;
    if(this->pos.x > 1)
        this->pos.x = -1;
}

// Move the host to the positon under itself
void Host::move_down(void){
    this->pos.y -= this->speed;
    if(this->pos.y < -1)
        this->pos.y = 1;
}

// Move the host to the positon on the left side of itself
void Host::move_left(void){
    this->pos.x -= this->speed;
    if(this->pos.x < -1)
        this->pos.x = 1;
}

// Function to create a single Host object
Host* create_initial_host() {
    float aggressiveness = generate_random(CONFIG["AGGRESSIVENESS_LOWER"], CONFIG["AGGRESSIVENESS_UPPER"]);
    float speed = generate_random(CONFIG["SPEED_LOWER"], CONFIG["SPEED_UPPER"]);
    float pos_x = generate_random(CONFIG["POS_X_LOWER"], CONFIG["POS_X_UPPER"]);
    float pos_y = generate_random(CONFIG["POS_Y_LOWER"], CONFIG["POS_Y_UPPER"]);
    float size = generate_random(CONFIG["SHAPE_LOWER"], CONFIG["SHAPE_UPPER"]);
    float fov = generate_random(CONFIG["FOV_LOWER"], CONFIG["FOV_UPPER"]);

    RGB_t color = {
        .R = generate_random(0, 1), .G = generate_random(0, 1), .B = generate_random(0, 1)
    };

    shape_t shape = {
        .h = size,
        .w = size
    };

    gene_t gene = {
        .shape = shape,
        .color = color,
        .fov = fov
    };
    
    position_t pos = {
        .x = pos_x,
        .y = pos_y
    };

    // Dynamically allocate memory for the Host object
    Host* host = new Host(aggressiveness, speed, gene, pos);

    return host;
}

// Increase hosts energy until it reaches a limit
void Host::increase_energy(Food *food) {
    if(food == NULL) return;

    if(this->energy + food->getEnergyPerUnit() < CONFIG["MAX_ENERGY"])
        this->energy += food->getEnergyPerUnit();
}

// Calculate host's energy loss based on charactristics
float Host::calculate_energy_loss(){
    float loss = 0;
    loss += CONFIG["ENERGY_LOSS_MODIFIER_SPEED"] * (this->speed);
    loss += CONFIG["ENERGY_LOSS_MODIFIER_SHAPE"] * (this->gene.shape.h);
    loss += CONFIG["ENERGY_LOSS_MODIFIER_FOV"] * (this->gene.fov);
    return loss;
}

// See if host meets the requirements for dying
bool Host::should_host_die(int *number_of_living_hosts) {
    if(this->energy <= 0 && this->state != DEAD) {
        std::cout << "running low on energy: killing host :(\n";
        (*number_of_living_hosts)--;
        return true;
    }
    return false;
}

// Decrease hosts energy
void Host::decrease_energy(float subtracted_qtd) {
    this->energy -= subtracted_qtd;
}

// Calculate host's speed based on its own size
float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
                                    float size_lower_bound, float size_upper_bound, float size) {

    float speed = (size_upper_bound - size) / (size_upper_bound / speed_upper_bound);

    return speed;
}

// Mutate host's characteristics
void Host::mutate() {
    this->gene.shape.h = mutate_float_value(this->gene.shape.h);
    this->gene.shape.w = this->gene.shape.h;

    this->speed = calculate_speed_based_on_size(CONFIG["SPEED_UPPER"], CONFIG["SPEED_LOWER"], 
            CONFIG["SHAPE_LOWER"], CONFIG["SHAPE_UPPER"], this->gene.shape.h);

    this->gene.color.R = mutate_color(this->gene.color.R);
    this->gene.color.G = mutate_color(this->gene.color.G);
    this->gene.color.B = mutate_color(this->gene.color.B);

    this->aggressiveness = mutate_float_value(this->aggressiveness);

    this->gene.fov = mutate_float_value(this->gene.fov);
}

// Mutation of a float value
float Host::mutate_float_value(float value) {
    int factor = 1;
    float mutated_value;
    
    if(coin_toss())
        factor = -1;

    mutated_value = abs((value + factor * (CONFIG["MUTATION_ADDITIVE_MODIFIER"] / 2)) * 
        (1 + factor * CONFIG["MUTATION_MULTIPLICATIVE_MODIFIER"]));

    return mutated_value;
}

// Mutation of color
float Host::mutate_color(float color_value) {
    int factor = 1;
    float color;
    if(coin_toss()) {
        factor = -1;
    }
    color = abs(color_value + factor * CONFIG["MUTATION_ADDITIVE_MODIFIER"]);
    return color > 1 ? color - 1 : color;
}

// A coin toss mechanism for 50% probability cases
bool Host::coin_toss() {
    int rand = generate_random_integer(0, 99);
    return rand % 2;
}

// Update host situation based on his current state
void Host::update(std::vector<Food>& foods, int *number_of_living_hosts) {
    switch (this->state) {
        case LOOKING_FOR_FOOD: {
            position_t random = { generate_random(-1, 1), generate_random(-1, 1) };

            this->random_movement_timer--;

            if(this->comparePositionsWithTolerance(this->going_to, this->pos, 0.05) || 
                this->random_movement_timer == 0) {
                this->going_to = random;
                this->random_movement_timer = CONFIG["RANDOM_MOVEMENT_TIMER"];
            }

            this->goTo(this->going_to);
            if(findFoodInVision(foods))
                this->state = GOING_TO_FOOD;
                
            break;
        }
        case GOING_TO_FOOD:
            this->goToFood();
            if(this->hasFoundFood()){
                this->state = EATING;
                if(this->energy / 100 < this->aggressiveness)
                        this->state = TARGETING;
            }
            break;
        case EATING:
            if(!this->eat(currentFood))
                this->state = LOOKING_FOR_FOOD;
            break;
        case TARGETING:
            this->battle(currentFood);
            this->state = EATING;
            break;
        case TARGETED:
            if(currentFood == NULL || (currentFood != NULL && currentFood->getTimer() <= 0))
                this->state = LOOKING_FOR_FOOD;
            break;
        case ATTACKING:
            /* code */
            break;
        case DEFENDING:
            /* code */
            break;
        case FLEEING:
            /* code */
            break;
        case DEAD:
            break;
        default:
            break;
    }

    //Every time you update you lose energy
    this->decrease_energy(calculate_energy_loss());

    if(should_host_die(number_of_living_hosts)) {
        this->state = DEAD;
    }
    
    if(this->state != DEAD) {
        this->show_host();
        if(this->currentFood != NULL)
            this->currentFood->update();
    }
}

// Make a host "eat" the food
bool Host::eat(Food *food) {
    // Decrement the timer
    //eatingTimer--;
    if (food != NULL)
        food->decreaseTimer();

    // increase hosts's energy while eating
    this->increase_energy(food);

    if (food == NULL || (food != NULL && food->getTimer() <= 0)) {
        // Eating time is over, remove the consumed food
        return false;
        // Optionally, you can reset the timer or perform other actions
    }
    return true;
}

// Make a host battle another for energy
void Host::battle(Food *food) {
    Host *host2;
    
    int energy;

    if(food == NULL)
        return;

    if(food->eatingHostsSize() > 1){
        int h = generate_random_integer(0, (food->eatingHostsSize()) - 2);
        host2 = food->getHost(h);
        if(this->gene.shape.h > host2->gene.shape.h){
            energy = host2->energy * CONFIG["AGGRESSIVENESS_GAIN"];
            this->energy += energy;
            if (this->energy > CONFIG["MAX_ENERGY"])
                this->energy = CONFIG["MAX_ENERGY"];
            host2->energy -= energy;
            //host2->state = TARGETED;
        } else {
            energy = this->energy * CONFIG["AGGRESSIVENESS_GAIN"];
            this->energy -= energy;
            host2->energy += energy;
            if (host2->energy > CONFIG["MAX_ENERGY"])
                host2->energy = CONFIG["MAX_ENERGY"];
            //this->state = TARGETED;
        }
    }
}

// Tries to find food in the host field of vision
bool Host::findFoodInVision(std::vector<Food>& foods) {
    float visionRadius = this->gene.fov;

    for (auto& food : foods) {
        float dx = food.getX() - this->pos.x;
        float dy = food.getY() - this->pos.y;
        float distance = sqrt(pow(dx, 2) + pow(dy, 2));

        if (distance <= visionRadius) {
            this->currentFood = &food; // Food found in the field of vision
            return true;
        }
    }

    return false; // Indicates that no food was found
}

// Make host go to a position
void Host::goTo(position_t position) {
    float dx = position.x - this->pos.x;
    float dy = position.y - this->pos.y;

    if(abs(dx) < 0.05)
        dx = 0;
    if(abs(dy) < 0.05)
        dy = 0;

    float d = sqrt(dx*dx + dy*dy);

    if (d > 0) {
        float cos = dx / d;
        float sin = dy / d;

        this->pos.x += this->speed * cos;
        this->pos.y += this->speed * sin;
    }

    float halfWidth = this->gene.shape.w / 2;
    float halfHeight = this->gene.shape.h / 2;

    if (this->pos.x - halfWidth < -1) 
        this->pos.x = -1 + halfWidth;
    else if (this->pos.x + halfWidth > 1) 
        this->pos.x = 1 - halfWidth;

    if (this->pos.y - halfHeight < -1) 
        this->pos.y = -1 + halfHeight;
    else if (this->pos.y + halfHeight > 1) 
        this->pos.y = 1 - halfHeight;
}

// Make host got to a food
void Host::goToFood() {
    this->goTo({ this->currentFood->getX(), this->currentFood->getY() });
}

// Check if host has found food
bool Host::hasFoundFood() {
    float food_x = currentFood->getX();
    float food_y = currentFood->getY();
    float food_width = currentFood->getWidth();
    float food_height = currentFood->getHeight();
    if (this->pos.x - this->gene.shape.w / 2 < food_x + food_width / 2 &&
        this->pos.x + this->gene.shape.w / 2 > food_x - food_width / 2 &&
        this->pos.y - this->gene.shape.h / 2 < food_y + food_height / 2 &&
        this->pos.y + this->gene.shape.h / 2 > food_y - food_height / 2) {
        
        // The host is in contact with the food
        // Perform the eating action
        currentFood->registerHost(this);

        // Meme contamination
        currentFood->contaminateHosts(this);

        return true;
    }
    return false;
}

// Compare two positons with a given tolerance
bool Host::comparePositionsWithTolerance(position_t pos1, position_t pos2, float tolerance) {
    return abs(pos1.x - pos2.x) <= tolerance && abs(pos1.y - pos2.y) <= tolerance;
}