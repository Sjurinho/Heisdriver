#include "elev.h"
#include "utilities.h"
#include "control.h"
#include <stdio.h>

int main() { 
    current_state = INITIALIZE;
    while(current_state != FAIL){
	if (elev_get_stop_signal()){
		next_state=STOP_SIGNAL;	
		if (stop){
			printStop();
			stop = 0;
			}
		}
        current_state = stateControl(current_state);  
            if(elev_get_obstruction_signal()){ //stopp programmet ved å flikke bryteren aktiv 
	    	    printOrder();      //skriver ut ordrene når bryteren er flikket 
                elev_set_motor_direction(DIRN_STOP);
		printf("\nOrder_size: %d ", get_order_size());
                break;
        }
        // Stop elevator and exit program if the obstruction button is pressed
	}
    return 0;
}
