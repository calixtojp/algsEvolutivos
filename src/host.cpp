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

void Host::change_size(float new_size){
    this->size = new_size;
}

void Host::change_color(float new_R, float new_G, float new_B){
    this->color.R = new_R;
    this->color.G = new_G;
    this->color.B = new_B;
}

void Host::show_characteristics(){
    printf("x:%.2f|y:%.2f|size:%.2f|RGB(%.2f,%.2f,%.2f)\n",
        this->pos.x,
        this->pos.y,
        this->size,
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
    glVertex2d(this->pos.x-this->size/2, this->pos.y-this->size/2);
    glVertex2d(this->pos.x-this->size/2, this->pos.y+this->size/2);
    glVertex2d(this->pos.x+this->size/2, this->pos.y+this->size/2);
    glVertex2d(this->pos.x+this->size/2, this->pos.y-this->size/2);

    glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}

void Host::move_up(void){
    this->pos.y += this->speed;
    this->pos.y = this->pos.y>1 ? -1 : this->pos.y;
}

void Host::move_right(void){
    this->pos.x += this->speed;
    this->pos.x = this->pos.x>1 ? -1 : this->pos.x;
}

void Host::move_down(void){
    this->pos.y -= this->speed;
    this->pos.y = this->pos.y>1 ? -1 : this->pos.y;
}

void Host::move_left(void){
    this->pos.x -= this->speed;
    this->pos.x = this->pos.x>1 ? -1 : this->pos.x;
}

float generate_random(float lower, float upper) {
    // Initialize a random number generator engine
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Use the Mersenne Twister engine
    std::uniform_real_distribution<float> distribution(lower, upper);

    // Generate and return a random float in the specified range
    return distribution(gen);
}

// Function to create a single Host object
Host* create_host() {
    float reproductionrate = generate_random(0, 1);
    float speed = generate_random(0, 1);
    float size = generate_random(0.1, 0.2);

    
    float aggressiveness = generate_random(0, 1);
    float pos_x = generate_random(-1, 1);
    float pos_y = generate_random(-1, 1);

    // Dynamically allocate memory for the Host object
    Host* temp = new Host(speed, aggressiveness, reproductionrate, size);

    temp->change_position(pos_x, pos_y);
    temp->change_color(0, 0, 1);
    temp->change_size(size);

    temp->show_characteristics();

    return temp;
}

void create_initial_population(vector<Host*> &Hosts, int hosts_qty) {
    for (int i = 0; i < hosts_qty; ++i) {
        Host* temp = create_host();
        Hosts.push_back(temp);
    }
}
