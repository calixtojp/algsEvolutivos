#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <bits/stdc++.h>

#include "utils.h"
#include "host.h"
#include "food.h"

using std::vector;
using std::priority_queue;

class World {
    vector <Host*> Hosts;  
    vector <Food> Foods;
    

    int hosts_qtd;
    int number_of_living_hosts;
    int generation;

public:


    World(int hosts_qtd) : hosts_qtd(hosts_qtd) {
        create_initial_population(this->Hosts, this->hosts_qtd);
        create_food_population((this->Foods), this->hosts_qtd / 2);
        this->number_of_living_hosts = this->hosts_qtd;
    }

    /*
        Acho q seria uma boa a gente dividir esse método update em outros métodos mais atômicos:
        - run_simulation
        - select_algorithm
        - mutations
    */
    void update();


    void run_reproduction_algorithm();
    Host *tournament_selection();
    void create_initial_population(vector <Host*> &Hostes, int hostes_qtd);
    Host *reproduce_hosts(Host *parent_1, Host *parent_2);
    void clear_population(std::vector<Host*>& Hosts);
};

#endif