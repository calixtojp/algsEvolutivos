#ifndef INTERACTMANAGER_H
#define INTERACTMANAGER_H

#include <stdio.h>
#include <bits/stdc++.h>

#include "utils.h"
#include "host.h"
#include "food.h"

using std::vector;
using std::map;

//Object positions. These objects are the food or the host.
typedef struct objPos{
    bool IsHost; //True if is host. False if is food.
    int posInVector;//The position of the object um vector
}ObjPos;

//Stores a map of object positions in a dimension.
typedef map<float, ObjPos> mapPos1D;

//Stores the position of the object given the dimensions X, Y
typedef struct mapPos{
    mapPos1D xDim; // map on x dimension
    mapPos1D yDim; //map on x dimension
}mapPos_t;

class Manager {

private:

    mapPos_t mp;

public:
    vector <Host*> Hostes;  
    vector <Food> Foods;
    int hostes_qtd;

    Manager(int hostes_qtd){
        this->hostes_qtd = hostes_qtd;
    }

    void show_hosts();
    void update_hosts();
    // void show_foods();
    // void wake_up_host();

};

#endif