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
    this->shape.h = new_h;
    this->shape.w = new_w;
}

void Host::change_color(float new_R, float new_G, float new_B){
    this->color.R = new_R;
    this->color.G = new_G;
    this->color.B = new_B;
}

void Host::show_characteristics(){
    printf("x:%.2f|y:%.2f|h:%.2f|w:%.2f|RGB(%.2f,%.2f,%.2f)\n",
        this->pos.x,
        this->pos.y,
        this->shape.h,
        this->shape.w,
        this->color.R,
        this->color.G,
        this->color.B
    );
}

void Host::show_host(void){
    // Vai desenhar um polígono de 4 vértices
    // this->show_characteristics();

    glColor3f(this->color.R, this->color.G, this->color.B);
    glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

    // Adicionada cada vértice do retângulo
    glVertex2d(this->pos.x-this->shape.w/2, this->pos.y-this->shape.h/2);
    glVertex2d(this->pos.x-this->shape.w/2, this->pos.y+this->shape.h/2);
    glVertex2d(this->pos.x+this->shape.w/2, this->pos.y+this->shape.h/2);
    glVertex2d(this->pos.x+this->shape.w/2, this->pos.y-this->shape.h/2);

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
Host* create_host() {
    float speed = generate_random(0, 1);
    float aggressiveness = generate_random(0, 1);
    float reproductionrate = generate_random(0, 1);
    float pos_x = generate_random(-1, 1);
    float pos_y = generate_random(-1, 1);
    float shape = generate_random(0.1, 0.2);

    // Dynamically allocate memory for the Host object
    Host* host = new Host(speed, aggressiveness, reproductionrate);

    host->change_position(pos_x, pos_y);
    host->change_color(0, 0, 1);
    host->change_shape(shape, shape);

    host->show_characteristics();

    return host;
}

// Function to create and add multiple Hosts to a vector
void create_initial_population(std::vector<Host*>& Hosts, int hosts_qty) {
    for (int i = 0; i < hosts_qty; ++i) {
        Host* temp = create_host();
        Hosts.push_back(temp);
    }
}

// Function to delete all Host objects in the vector and clear it
void clear_population(std::vector<Host*>& Hosts) {
    for (auto host : Hosts) {
        delete host; // Deallocate memory for each Host
    }
    Hosts.clear(); // Clear the vector
}

void Host::interact_with_food(std::vector<Food>& foods) {
    // Check if the host is already eating
    if (isEating) {
        // Decrement the timer
        eatingTimer--;

        //currentFood->setTimer(eatingTimer); // Why this is segfault?

        if (eatingTimer <= 0) {
            // Eating time is over, remove the consumed food
            isEating = false;

            currentFood->setTimer(500);
            currentFood->randPosition();


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
            if (pos.x - shape.w / 2 < food_x + food_width / 2 &&
                pos.x + shape.w / 2 > food_x - food_width / 2 &&
                pos.y - shape.h / 2 < food_y + food_height / 2 &&
                pos.y + shape.h / 2 > food_y - food_height / 2) {
                
                // The host is in contact with the food
                // Perform the eating action
                isEating = true;
                
                // Store the currently interacting food
                currentFood = &food;

                eatingTimer = currentFood->getTimer(); // Set a timer (adjust as needed)

                // Optionally, you can do more, such as increasing a score, etc.
            }
        }
    }
}