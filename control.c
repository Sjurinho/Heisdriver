#include <stdio.h>
#include "control.h"
#include "timer.h"
#include "utilities.h"
#include "elev.h"

int lastDir = -9;
enum State stateControl(enum State CURRENT_STATE){
     switch (CURRENT_STATE) {
        case INITIALIZE:
            if (!elev_init()){
                printf("Hardware is not initialized");
                NEXT_STATE = FAIL;
        	    break;
            }
            initialize(); 
            NEXT_STATE = TAKEORDER;
            break;
       case TAKEORDER:
            set_order();
            if(get_orderSize() !=  0){
                NEXT_STATE = DRIVE;
	            NEXT_FLOOR  = get_floor();
	    	if(CURRENT_FLOOR > NEXT_FLOOR){
                DIRECTION_UP = 0;
            }
            else if(CURRENT_FLOOR < NEXT_FLOOR){
                DIRECTION_UP = 1;
            }
	    	else if(elev_get_floor_sensor_signal() == -1 && NEXT_FLOOR==CURRENT_FLOOR){
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
            NEXT_FLOOR = get_floor();
            set_floor(); 
	        if (elev_get_floor_sensor_signal() == -1 && NEXT_FLOOR != CURRENT_FLOOR){
	           lastDir = DIRECTION_UP;
	        }
    	    elev_set_stop_lamp(0);
	        set_order();
	        drive(DIRECTION_UP);
	        if(find_collision()){
	           NEXT_STATE = ARRIVED;
               start_timer();
            }
            else if(elev_get_floor_sensor_signal() == NEXT_FLOOR){
                start_timer();
                NEXT_STATE = ARRIVED;
            }
            break;
        case ARRIVED:
            stop_elevator();
            elev_set_door_open_lamp(1);
            set_order();
            set_floor();
            reset_order(CURRENT_FLOOR);
            if(check_timer(3.0)){
                elev_set_door_open_lamp(0);
                NEXT_STATE = TAKEORDER;
            }
	        break;
        case STOP_SIGNAL: 
            while (elev_get_stop_signal()){
                set_stop();
                start_timer();
            }
            elev_set_stop_lamp(0);
            if(elev_get_floor_sensor_signal()!=-1){
                NEXT_STATE=ARRIVED;
                break;
            }     
            NEXT_STATE=TAKEORDER;
            break;      
        case FAIL:
            stop_elevator();
            printf("FAILURE");
            NEXT_STATE = INITIALIZE;
    	    break;
    	default:
    	    break;
    }
	return NEXT_STATE;
}



