#include "elev.h"
//#include "statemachine.h"
#include "door.h"
#include "utilities.h"
#include "control.h"
#include <stdio.h>

int main() { 
    current_state = INITIALIZE;
    while(current_state != FAIL){
        current_state = stateControl(current_state);  
    
    
            if(elev_get_obstruction_signal()){
                elev_set_motor_direction(DIRN_STOP);
                break;
        }
        // Stop elevator and exit program if the obstruction button is pressed
    
	if (current_state == FAIL){
		return 1;
	}
	}
    return 0;
}
