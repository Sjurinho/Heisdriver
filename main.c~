#include "elev.h"
#include "utilities.h"
#include "control.h"
#include <stdio.h>
#include <time.h>

int main() { 
    currentState = INITIALIZE;
    while(currentState != FAIL){
	usleep(50000);
	if (elev_get_stop_signal()){
		nextState=STOP_SIGNAL;	
		print_stop();
	}
        currentState = stateControl(currentState);  
            if(elev_get_obstruction_signal()){ //stopp programmet ved å flikke bryteren aktiv 
	    	    print_order();      //skriver ut ordrene når bryteren er flikket 
                elev_set_motor_direction(DIRN_STOP);
		printf("\nOrder_size: %d ", get_orderSize());
                break;
        }
        // Stop elevator and exit program if the obstruction button is pressed
	}
    return 0;
}
