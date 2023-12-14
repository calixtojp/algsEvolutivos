#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include "interactManager.h"
#include <stdio.h>

void Manager::show_hosts(void){
    printf("existem %d hosts\n", this->hostes_qtd);
    // Display the hosts
    for (auto it : this->Hostes) {
        it->show_host();
    }
}

void Manager::update_hosts(void){
    for(auto it : this->Hostes) {
        it->decrease_energy();
        it->kill_host_if_energy_is_zero();

        if(!it->is_alive) return;
        
        
                
    }
}