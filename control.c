#include <stdio.h>
#include "control.h"
#include "timer.h"
#include "utilities.h"
#include "elev.h"

int lastDir = -9;
enum State stateControl(enum State currentState){
     switch (currentState) {
        case INITIALIZE:
            if (!elev_init()){
                printf("Hardware is not initialized");
                nextState = FAIL;
        	    break;
            }
            initialize(); 
            nextState = TAKEORDER;
            break;
       case TAKEORDER:
            set_order();
            if(get_orderSize() !=  0){
                nextState = DRIVE;
	            nextFloor  = get_floor();
	    	if(currentFloor > nextFloor){
                DIRECTION_UP = 0;
            }
            else if(currentFloor < nextFloor){
                DIRECTION_UP = 1;
            }
	    	else if(elev_get_floor_sensor_signal() == -1 && nextFloor==currentFloor){
		 	    if (lastDir == 0){
		    	    DIRECTION_UP = 1;
		 	    }
		 	    else if(lastDir == 1){
                    DIRECTION_UP = 0;
                } 
	    	} 
		}
            break;
        case DRIVE:
            nextFloor = get_floor();
            set_floor(); 
	        if (elev_get_floor_sensor_signal() == -1 && nextFloor != currentFloor){
	           lastDir = DIRECTION_UP;
	        }
    	    elev_set_stop_lamp(0);
	        set_order();
	        drive(DIRECTION_UP);
	        if(find_collision()){
	           nextState = ARRIVED;
               start_timer();
            }
            else if(elev_get_floor_sensor_signal() == nextFloor){
                start_timer();
                nextState = ARRIVED;
            }
            break;
        case ARRIVED:
            stop_elevator();
            elev_set_door_open_lamp(1);
            set_order();
            set_floor();
            reset_order(currentFloor);
            if(check_timer(3.0)){
                elev_set_door_open_lamp(0);
                nextState = TAKEORDER;
            }
	        break;
        case STOP_SIGNAL: 
            while (elev_get_stop_signal()){
                set_stop();
                start_timer();
            }
            elev_set_stop_lamp(0);
            if(elev_get_floor_sensor_signal()!=-1){
                nextState=ARRIVED;
                break;
            }     
            nextState=TAKEORDER;
            break;      
        case FAIL:
            stop_elevator();
            printf("FAILURE");
            nextState = INITIALIZE;
    	    break;
    	default:
    	    break;
    }
	return nextState;
}

