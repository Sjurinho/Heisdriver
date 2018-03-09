#include "elev.h"
#include "utilities.h"
#include "control.h"
#include <stdio.h>
#include <time.h>

int main() { 
    CURRENT_STATE = INITIALIZE;
    while(CURRENT_STATE != FAIL){
	if (elev_get_stop_signal()){
		NEXT_STATE = STOP_SIGNAL;	
	}
        CURRENT_STATE = stateControl(CURRENT_STATE);  
            if(elev_get_obstruction_signal()){ //stopp programmet ved å flikke bryteren aktiv 
                elev_set_motor_direction(DIRN_STOP);
                break;
        }
        // Stop elevator and exit program if the obstruction button is pressed
	}
    return 0;
}
