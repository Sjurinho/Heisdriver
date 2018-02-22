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
        if (time_spent >= time_wait){ //sjekker om det har gått mer enn 3 sek
            break;
        }
    }
}



void door_delay(int time_wait){ //stopper heisen i tre sekunder og setter på lys
    stop_elevator();
    open_door(); 
    timer(time_wait);
    close_door(); 
	elev_set_door_open_lamp(0);
    timer(0.5); //Gir heisen 0.5 sek til å starte igjen slik at den ikke er stuck i en etasje
}
