#include "elev.h"
#include "utilities.h"
#include "control.h"
#include <stdio.h>
#include <time.h>

int main() { 
    currentState = INITIALIZE;
    while(currentState != FAIL){
	if (elev_get_stop_signal()){
		nextState = STOP_SIGNAL;	
	}
        currentState = stateControl(currentState);  
            if(elev_get_obstruction_signal()){ //stopp programmet ved å flikke bryteren aktiv 
                elev_set_motor_direction(DIRN_STOP);
                break;
        }
        // Stop elevator and exit program if the obstruction button is pressed
	}
    return 0;
}
