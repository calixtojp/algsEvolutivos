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
    printf("x:%.2f|y:%.2f|h:%.2f|w:%.2f|RGB(%.2f,%.2f,%.2f)\n",
        this->pos.x,
        this->pos.y,
        this->gene.shape.h,
        this->gene.shape.w,
        this->gene.color.R,
        this->gene.color.G,
        this->gene.color.B
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
    //this->pos.y = this->pos.y>1 ? -1 : this->pos.y;
}

void Host::move_right(void){
    this->pos.x += this->speed;
    if(this->pos.x > 1){
        this->pos.x = -1;
        this->pos.y = generate_random(-1, 1);
    }
    //this->pos.x = this->pos.x>1 ? -1 : this->pos.x;
}

void Host::move_down(void){
    this->pos.y -= this->speed;
    if(this->pos.y < -1){
        this->pos.y = 1;
        this->pos.x = generate_random(-1, 1);
    }
    //this->pos.y = this->pos.y<-1 ? 1 : this->pos.y;
}

void Host::move_left(void){
    this->pos.x -= this->speed;
    if(this->pos.x < -1){
        this->pos.x = 1;
        this->pos.y = generate_random(-1, 1);
    }
    //this->pos.x = this->pos.x<-1 ? 1 : this->pos.x;
}

// Function to create a single Host object
Host* create_initial_host() {
    float aggressiveness = generate_random(AGGRESSIVENESS_LOWER, AGGRESSIVENESS_UPPER);
    float reproductionrate = generate_random(REPRODUCTIONRATE_LOWER, REPRODUCTIONRATE_UPPER);
    float pos_x = generate_random(POS_X_LOWER, POS_X_UPPER);
    float pos_y = generate_random(POS_Y_LOWER, POS_Y_UPPER);
    float size = generate_random(SHAPE_LOWER, SHAPE_UPPER);

    RGB_t color = {
        .R = 0, .G = 0, .B = 1
    };

    shape_t shape = {
        .h = size,
        .w = size
    };

    gene_t gene = {
        .shape = shape,
        .color = color
    };
    
    position_t pos = {
        .x = pos_x,
        .y = pos_y
    };

    // Dynamically allocate memory for the Host object
    Host* host = new Host(aggressiveness, reproductionrate, gene, pos);

    return host;
}

// Function to delete all Host objects in the vector and clear it


void Host::interact_with_food(std::vector<Food>& foods) {
    // Check if the host is already eating
    if (isEating) {
        // Decrement the timer
        //eatingTimer--;
        if (currentFood != NULL)
            currentFood->decreaseTimer();

        // increase hosts's energy while eating
        this->increase_energy(currentFood);

        //currentFood->setTimer(eatingTimer); // Why this is segfault?

        if (currentFood != NULL && currentFood->getTimer() <= 0) {
            // Eating time is over, remove the consumed food
            isEating = false;
            // Optionally, you can reset the timer or perform other actions
        }
    } else {
        // Iterate through all foods to check for interaction
        for (auto& food : foods) {
            float food_x = food.getX();
            float food_y = food.getY();
            float food_width = food.getWidth();
            float food_height = food.getHeight();

            // Check if the host is in contact with the food
            if (pos.x - gene.shape.w / 2 < food_x + food_width / 2 &&
                pos.x + gene.shape.w / 2 > food_x - food_width / 2 &&
                pos.y - gene.shape.h / 2 < food_y + food_height / 2 &&
                pos.y + gene.shape.h / 2 > food_y - food_height / 2) {
                
                // The host is in contact with the food
                // Perform the eating action
                isEating = true;
                food.registerHost(this);

                // Meme contamination
                //food.contaminateHosts(this);

                // Store the currently interacting food
                currentFood = &food;

                //eatingTimer = currentFood->getTimer(); // Set a timer (adjust as needed)

                // Optionally, you can do more, such as increasing a score, etc.
            }
        }
    }
}

void Host::increase_energy(Food *food) {
    if(food == NULL) return;

    if(this->energy + food->getEnergyPerUnit() < MAX_ENERGY)
        this->energy += food->getEnergyPerUnit();
}

void Host::kill_host_if_energy_is_zero(int *number_of_living_hosts) {
    if(this->energy <= 0 && this->is_alive) {
        std::cout << "running low on energy: killing host :(\n";
        (*number_of_living_hosts)--;
        this->is_alive = false;
    }
}

void Host::decrease_energy() {
    this->energy -= ENERGY_LOSS_PER_TICK;
}

void Host::update(std::vector<Food>& foods, int *number_of_living_hosts) {
    this->decrease_energy();
    this->kill_host_if_energy_is_zero(number_of_living_hosts);
    
    if(!this->is_alive) return;

    this->show_host();

    // Check food interactions for each host
    this->interact_with_food(foods);

    if(this->currentFood != NULL)
        this->currentFood->update();

    // Update host state (including movement) based on the eating mechanic
    if(!(this->isEating)) this->move_left();
}

float calculate_speed_based_on_size(float speed_upper_bound, float speed_lower_bound, 
                                    float size_lower_bound, float size_upper_bound, float size) {
    float size_magnitude = size / (size_upper_bound - size_lower_bound);
    float speed = (1 / size_magnitude) * (speed_upper_bound - speed_lower_bound);

    std::cout << "creating host with speed: " << speed << '\n';

    return speed;
}

void Host::mutate() {
    int factor = 1;
    if(coin_toss())
        factor = -1;

    this->gene.shape.h = abs(this->gene.shape.h * (1 + factor * MUTATION_MULTIPLICATIVE_MODIFIER));
    this->gene.shape.w = abs(this->gene.shape.w * (1 + factor * MUTATION_MULTIPLICATIVE_MODIFIER));

    this->gene.color.R = mutate_color(this->gene.color.R);
    this->gene.color.G = mutate_color(this->gene.color.G);
    this->gene.color.B = mutate_color(this->gene.color.B);
}

float Host::mutate_color(float color_value) {
    int factor = 1;
    if(coin_toss()) {
        factor = -1;
    }
    return abs(color_value + factor * MUTATION_ADDITIVE_MODIFIER);
}

bool Host::coin_toss() {
    int rand = generate_random_integer(0, 99);
    return rand % 2;
}