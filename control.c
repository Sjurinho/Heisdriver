#include <stdio.h>
#include "control.h"
#include "timer.h"
#include "utilities.h"
#include "elev.h"

enum State stateControl(enum State currentState){
     switch (currentState) {
        case INITIALIZE:
            if (!elev_init()){
                printf("Hardware is not initialized");
                nextState = FAIL;
        		break;
            }
            initialize(); 
            print_floor();
            nextState = TAKEORDER;
            break;
       case TAKEORDER:
            set_order();
            if(get_orderSize() !=  0){
                nextState = DRIVE;
            }
	        nextFloor  = get_floor();
            break;
        case DRIVE:
	    nextFloor = get_floor();
            if(elev_get_floor_sensor_signal() != -1){
                currentFloor = elev_get_floor_sensor_signal(); 
                set_floor(); 
		printf("\nNext floor is: %d", nextFloor);
            }
    	    elev_set_stop_lamp(0);
	    set_order();
	    if(find_collision()){
	        nextState = ARRIVED;
		print_floor();
		start_timer();
            }
            else if(currentFloor > nextFloor){
                drive_down();
                direction = 0; 
            }
            else if(currentFloor < nextFloor){
                drive_up();
                direction = 1;
            }
            else if(elev_get_floor_sensor_signal() == nextFloor){
                print_floor();
                start_timer();
                nextState = ARRIVED;
            }
            else if(elev_get_floor_sensor_signal() == -1 && nextFloor == currentFloor){
               if(direction){
                    drive_down();
                }
                else{
                    drive_up(); 
                }
            }
            break;
        case ARRIVED:
	    stop_elevator();
	    elev_set_door_open_lamp(1);
            set_order();
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
            print_stop();
            printf("FAILURE");
            nextState = INITIALIZE;
    		break;
    	default:
    		break;
    }
	return nextState;
}











