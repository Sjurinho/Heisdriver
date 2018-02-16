<<<<<<< HEAD
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
=======
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
<<<<<<< HEAD
        if (time_spent> = time_wait){ //sjekker om det har gått mer enn 3 sek
            break;
        }
    }
=======
        if (time_spent >= time_wait){ //sjekker om det har gått mer enn 3 sek
            break;
        }
    }
}



void door_delay(int time_wait){ //stopper heisen i tre sekunder og setter på lys
    open_door(); 
    stop_elevator();
    elev_set_door_open_lamp(1);
    timer(time_wait);
    close_door(); 
    elev_set_door_open_lamp(0);
    drive_up(); //midlertidig funksjon for å starte heisen igjen (testing)
    timer(0.5); //Gir heisen 0.5 sek til å starte igjen slik at den ikke er stuck i en etasje
>>>>>>> origin
}



void door_delay(int time_wait){
    open_door(); 
    elev_set_door_open_lamp(1);
    timer(time_wait);
    close_door(); 
    elev_set_door_open_lamp(0);
}
>>>>>>> origin
