#include "statemachine.h"
#include "door.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void stateMachine(State next_state, elev_motor_direction_t dir){
	int orders[2] = { 0 };    
	switch (next_state){
        	case INITIALIZE:
            	if (!elev_init()){
                	printf("HARDWARE IS NOT PROPERLY INITIALIzED!!!");
                	next_state = FAIL;    
            	}
            	initialize();
		printf("HEIEHIEHEIHE");
            	next_state = TAKEORDER;
            	break;
        case TAKEORDER:
		//finner første arbeidsoppgave og legger dette inn i en tabell
            	for (int i = 0; i<N_FLOORS*2-2;i++){
                //	if (floorOrders[i] == 1){
                //    	orders[0] = (int) ((i/2.0) + 0.5);//indeksering bare
                //	}
            	}
		printf("MYAH");
            	next_state = DRIVE;
            	break;
        case DRIVE:
            	elev_set_motor_direction(dir); 
            	while (calculateFloor(orders[0]) < 0){
               		if(findCollision(orders[0])){
                    		next_state = DOOR;
                    		break;
                	} 
            	}
            	break;
        case DOOR:
            	door_delay(3.0,dir);
            	if (calculateFloor(orders[0])==0){
                	next_state = TAKEORDER;
            	}
            	else{next_state=DRIVE;}
        	break;
	case FAIL:
		printf("FAILURE");
		break;
	}
return next_state;
}
