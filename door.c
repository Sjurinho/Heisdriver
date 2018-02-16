#include "elev.h"
#include "utilities.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void door_delay(void){
    clock_t begin; 
    double time_spent; 
    stop_elevator(); //stopper heisen. 
    open_door(); //åpner døra
    begin = clock(); //starter klokka
    while(1){
        time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC; //teller opp
        if (time_spent>=3.0){ //sjekker om det har gått mer enn 3 sek
            close_door(); //lukker døra
            break;
        }
    }
    
}
