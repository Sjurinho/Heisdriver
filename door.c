#include "elev.h"
#include "utilities.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void timer(double time_wait){
    clock_t begin; 
    double time_spent; 
    begin = clock(); //starter klokka
    while(1){
        time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC; //teller opp
        if (time_spent> = time_wait){ //sjekker om det har gått mer enn 3 sek
            break;
        }
    }
}



void door_delay(int time_wait){
    open_door(); 
    elev_set_door_open_lamp(1);
    timer(time_wait);
    close_door(); 
    elev_set_door_open_lamp(0);
}
