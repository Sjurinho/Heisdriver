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
            print_floor();
            nextState = TAKEORDER;
            break;
       case TAKEORDER:
// KUN HER VI ENDRER kjøreretning
            set_order();
            if(get_orderSize() !=  0){
                nextState = DRIVE;
	        nextFloor  = get_floor();
	    	if(currentFloor > nextFloor){
			printf("\nBLUE");
                	direction = 0;
            	}
            	else if(currentFloor < nextFloor){
			printf("\nDABBADY DABBADA");
                	direction = 1;
            	}
	    	else if(elev_get_floor_sensor_signal() == -1 &&nextFloor==currentFloor){
			printf("\n \n out of TAKEORDER Em. STOP dir %d nextFLoor %d lastDir %d", direction, nextFloor, lastDir);
			//lastDir = direction;
		 	if (lastDir==0){
		    	direction = 1;
		 	}
		 	else if(lastDir==1){direction = 0;} 
	    		} 
		}
            break;
        case DRIVE:
	    nextFloor = get_floor();
	    //calculate_path();
            set_floor(); 
	    printf("\nDirection: %d last dir: %d",direction, lastDir);
	    if (elev_get_floor_sensor_signal() == -1 && nextFloor!=currentFloor){
	        lastDir = direction;
	    }
    	    elev_set_stop_lamp(0);
	    set_order();
	    drive(direction);
	    if(find_collision()){
	        nextState = ARRIVED;
		print_floor();
		start_timer();
            }

            else if(elev_get_floor_sensor_signal() == nextFloor){
                print_floor();
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
	    printf("\nNextFLOOR: %d",nextFloor+1);
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











