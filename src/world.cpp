#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "world.h"

// Update everything based on the current conditions
void World::update() {
    // Display the food
    for (const auto& food : this->Foods) {
        food.show_food();
    }

    // Update hosts
    for (auto it : this->Hosts) {
        it->update(this->Foods, &this->number_of_living_hosts);
    }

    // Reproduction Algorithm
    if(this->number_of_living_hosts <= 4.0/5.0 * hosts_qtd){
        run_reproduction_algorithm();
        printf("New group after reproduction:\n");
        for(auto h : Hosts)
            h->show_characteristics();
    }
        
        
}

// Reproduces hosts to fill the dead hosts spots
void World::run_reproduction_algorithm() {
    std::cout << "reproducing remaining hosts\n";

    auto host = Hosts.begin();

    while (host != Hosts.end()) {
        if ((*host)->state == DEAD) {
            Host *parent_1 = tournament_selection(); // Twos tournament
            Host *parent_2 = tournament_selection();

            if(parent_1 == NULL || parent_2 == NULL) {
                std::cout << "simulation is over: all hosts died :(((\n";
                exit(0);
            }

            Hosts.erase(host);

            Hosts.push_back(reproduce_hosts(parent_1, parent_2));

            this->number_of_living_hosts++;

            host--;
        } else {
            (*host)->mutate();
        }
        host++;
    }
}

// Twos tournament, gives priority to the highest energy
Host *World::tournament_selection() {
    if(this->number_of_living_hosts <= 0) return NULL;

    int first;
    do {
       first = generate_random_integer(0, hosts_qtd - 1);
    } while (this->Hosts.at(first)->state == DEAD);

    int second;
    do {
       second = generate_random_integer(0, hosts_qtd - 1);
    } while (this->Hosts.at(second)->state == DEAD);

    return this->Hosts.at(second)->energy > this->Hosts.at(first)->energy ? this->Hosts.at(second) : this->Hosts.at(first);
}

// Function to create the initial host population and add them to the Hosts vector
void World::create_initial_population(std::vector<Host*>& Hosts, int hosts_qty) {
    printf("Original group:\n");
    for (int i = 0; i < hosts_qty; ++i) {
        Host* temp = create_initial_host();
        Hosts.push_back(temp);
        temp->show_characteristics();
    }
}

// Two hosts reproduction mechanism
Host *World::reproduce_hosts(Host *parent_1, Host *parent_2) {
    gene_t gene;
    Host *host;
    float aggressiveness, speed;
    gene.color.R = (parent_1->gene.color.R + parent_2->gene.color.R) / 2;
    gene.color.G = (parent_1->gene.color.G + parent_2->gene.color.G) / 2;
    gene.color.B = (parent_1->gene.color.B + parent_2->gene.color.B) / 2;

    gene.shape.h = (parent_1->gene.shape.h + parent_2->gene.shape.h) / 2;
    gene.shape.w = (parent_1->gene.shape.w + parent_2->gene.shape.w) / 2;

    gene.fov = (parent_1->gene.fov + parent_2->gene.fov) / 2;

    aggressiveness = (parent_1->aggressiveness + parent_2->aggressiveness) / 2;
    speed = (parent_1->speed + parent_2->speed) / 2;

    host = new Host(aggressiveness, speed, gene, parent_1->pos);

    return host;
}

// Clear all host population
void World::clear_population(std::vector<Host*>& Hosts) {
    for (auto host : Hosts) {
        delete host; // Deallocate memory for each Host
    }
    Hosts.clear(); // Clear the vector
}