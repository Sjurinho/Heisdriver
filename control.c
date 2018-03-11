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
                NEXT_STATE = FAIL;
        	    break;
            }
            initialize(); 
            NEXT_STATE = TAKEORDER;
            break;
       case TAKEORDER:
            set_direction(lastDir);
            break;
        case DRIVE:
            NEXT_FLOOR = get_floor(); //continously update so path is optimal
            lastDir = drive_to_floor(lastDir);
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
            /*while (elev_get_stop_signal()){
                set_stop();
                start_timer();
            }
            elev_set_stop_lamp(0);
            if(elev_get_floor_sensor_signal()!=-1){
                NEXT_STATE=ARRIVED;
                break;
            } */
            stopping();
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



