#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "host.h"

int seed = 0;

void Host::change_position(float new_x, float new_y){
    this->pos.x = new_x;
    this->pos.y = new_y;
}

void Host::change_shape(float new_h, float new_w){
    this->gene.shape.h = new_h;
    this->gene.shape.w = new_w;
}

void Host::change_color(float new_R, float new_G, float new_B){
    this->gene.color.R = new_R;
    this->gene.color.G = new_G;
    this->gene.color.B = new_B;
}

void Host::show_characteristics(){
    printf("x:%.2f | y:%.2f | h:%.3f | w:%.3f | RGB(%.2f,%.2f,%.2f) | speed:%.3f | fov:%.3f\n",
        this->pos.x,
        this->pos.y,
        this->gene.shape.h,
        this->gene.shape.w,
        this->gene.color.R,
        this->gene.color.G,
        this->gene.color.B,
        this->speed,
        this->gene.fov
    );
}

void Host::show_host(void){
    // Vai desenhar um polígono de 4 vértices
    // this->show_characteristics();

    glColor3f(this->gene.color.R, this->gene.color.G, this->gene.color.B);
    glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

    // Adicionada cada vértice do retângulo
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y-this->gene.shape.h/2);
    glVertex2d(this->pos.x-this->gene.shape.w/2, this->pos.y+this->gene.shape.h/2);
    glVertex2d(this->pos.x+this->gene.shape.w/2, this->pos.y+this->gene.shape.h/2);
    glVertex2d(this->pos.x+this->gene.shape.w/2, this->pos.y-this->gene.shape.h/2);

    glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}

void Host::move_up(void){
    this->pos.y += this->speed;
    if(this->pos.y > 1){
        this->pos.y = -1;
        this->pos.x = generate_random(-1, 1);
    }
}

void Host::move_right(void){
    this->pos.x += this->speed;
    if(this->pos.x > 1){
        this->pos.x = -1;
        this->pos.y = generate_random(-1, 1);
    }
}

void Host::move_down(void){
    this->pos.y -= this->speed;
    if(this->pos.y < -1){
        this->pos.y = 1;
        this->pos.x = generate_random(-1, 1);
    }
}

void Host::move_left(void){
    this->pos.x -= this->speed;
    if(this->pos.x < -1){
        this->pos.x = 1;
        this->pos.y = generate_random(-1, 1);
    }
}

// Function to create a single Host object
Host* create_initial_host() {
    float aggressiveness = generate_random(CONFIG["AGGRESSIVENESS_LOWER"], CONFIG["AGGRESSIVENESS_UPPER"]);
    float reproductionrate = generate_random(CONFIG["REPRODUCTIONRATE_LOWER"], CONFIG["REPRODUCTIONRATE_UPPER"]);
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
    Host* host = new Host(aggressiveness, reproductionrate, gene, pos);

    return host;
}

void Host::increase_energy(Food *food) {
    if(food == NULL) return;

    if(this->energy + food->getEnergyPerUnit() < CONFIG["MAX_ENERGY"])
        this->energy += food->getEnergyPerUnit();
}

bool Host::should_host_die(int *number_of_living_hosts) {
    if(this->energy <= 0 && this->state != DEAD) {
        std::cout << "running low on energy: killing host :(\n";
        (*number_of_living_hosts)--;
        return true;
    }
    return false;
}

void Host::decrease_energy() {
    this->energy -= CONFIG["ENERGY_LOSS_PER_TICK"];
}

float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
                                    float size_lower_bound, float size_upper_bound, float size) {
    float size_magnitude = size / (size_upper_bound - size_lower_bound);
    float speed = pow((1 / size_magnitude), 2) * (speed_upper_bound - speed_lower_bound);

    return speed;
}

void Host::mutate() {
    int factor = 1;
    if(coin_toss())
        factor = -1;

    this->gene.shape.h = abs(this->gene.shape.h * (1 + factor * CONFIG["MUTATION_MULTIPLICATIVE_MODIFIER"]));
    this->gene.shape.w = abs(this->gene.shape.w * (1 + factor * CONFIG["MUTATION_MULTIPLICATIVE_MODIFIER"]));

    this->gene.color.R = mutate_color(this->gene.color.R);
    this->gene.color.G = mutate_color(this->gene.color.G);
    this->gene.color.B = mutate_color(this->gene.color.B);

    this->gene.fov = abs(this->gene.fov * (1 + factor * CONFIG["MUTATION_MULTIPLICATIVE_MODIFIER"]));
}

float Host::mutate_color(float color_value) {
    int factor = 1;
    float color;
    if(coin_toss()) {
        factor = -1;
    }
    color = abs(color_value + factor * CONFIG["MUTATION_ADDITIVE_MODIFIER"]);
    return color > 1 ? color - 1 : color;
}

bool Host::coin_toss() {
    int rand = generate_random_integer(0, 99);
    return rand % 2;
}

void Host::update(std::vector<Food>& foods, int *number_of_living_hosts) {
    switch (this->state) {
        case LOOKING_FOR_FOOD: {
            position_t random = { generate_random(-1, 1), generate_random(-1, 1) };
            if(this->random_movement_timer == 0) {
                this->random_movement_timer = CONFIG["RANDOM_MOVEMENT_TIMER"];
            }
            if(this->random_movement_timer == CONFIG["RANDOM_MOVEMENT_TIMER"]) {
                this->going_to = random;
            }
            this->random_movement_timer--;

            this->goTo(this->going_to);
            if(findFoodInVision(foods))
                this->state = GOING_TO_FOOD;
            break;
            }
        case GOING_TO_FOOD:
            this->goToFood();
            if(this->hasFoundFood())
                this->state = EATING;
            break;
        case EATING:
            if(!this->eat(currentFood))
                this->state = LOOKING_FOR_FOOD;
            break;
        case TARGETING:
            /* code */
            break;
        case TARGETED:
            /* code */
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

    this->decrease_energy();
    if(should_host_die(number_of_living_hosts)) {
        this->state = DEAD;
    }
    if(this->state != DEAD) {
        this->show_host();
        if(this->currentFood != NULL)
            this->currentFood->update();
    }
}

bool Host::eat(Food *food) {
    // Decrement the timer
    //eatingTimer--;
    if (food != NULL)
        food->decreaseTimer();

    // increase hosts's energy while eating
    this->increase_energy(food);

    //currentFood->setTimer(eatingTimer); // Why this is segfault?

    if (food == NULL || (food != NULL && food->getTimer() <= 0)) {
        // Eating time is over, remove the consumed food
        return false;
        // Optionally, you can reset the timer or perform other actions
    }
    return true;
}

bool Host::findFoodInVision(std::vector<Food>& foods) {
    float visionRadius = this->gene.fov;

    for (auto& food : foods) {
        float dx = food.getX() - this->pos.x;
        float dy = food.getY() - this->pos.y;
        float distance = sqrt(pow(dx, 2) + pow(dy, 2));

        if (distance <= visionRadius) {
            this->currentFood = &food; // Comida encontrada no campo de visão
            return true;
        }
    }

    return false; // Indica que nenhuma comida foi encontrada
}

void Host::goTo(position_t position) {
    float x_factor = position.x - this->pos.x;
    float y_factor = position.y - this->pos.y;
    std::stack<enum Direction> directions;
    
    if(x_factor > 0)
        directions.push(RIGHT);
    else
        directions.push(LEFT);
    
    if(y_factor > 0)
        directions.push(UP);
    else
        directions.push(DOWN);

    while(directions.size() > 0) {
        switch (directions.top()) {
            case LEFT:
                this->move_left();
                break;
            case RIGHT:
                this->move_right();
                break;
            case UP:
                this->move_up();       
                break;
            case DOWN:
                this->move_down();
                break;
            default:
                break;
        }
        directions.pop();
    }
}

void Host::goToFood() {
    this->goTo({ this->currentFood->getX(), this->currentFood->getY() });
}

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