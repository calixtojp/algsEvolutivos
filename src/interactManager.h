#ifndef INTERACTMANAGER_H
#define INTERACTMANAGER_H

#include <stdio.h>
#include <bits/stdc++.h>

#include "utils.h"
#include "host.h"
#include "food.h"

using std::vector;
using std::priority_queue;

class Manager {
    vector <Host*> Hostes;  
    vector <Food> Foods;
    int hostes_qtd;

    Manager(int hostes_qtd)
        : hostes_qtd(hostes_qtd) {

        create_initial_population(this->Hostes, this->hostes_qtd);
        create_food_population((this->Foods), this->hostes_qtd);

    }


};

#endif