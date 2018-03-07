#include <stdio.h>
#include "control.h"
#include "door.h"
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
            if(get_order_size() !=  0){
                nextState = DRIVE;
            }
	    nextFloor  = get_floor();
            break;
        case DRIVE:
            if(elev_get_floor_sensor_signal() != -1){
                currentFloor = elev_get_floor_sensor_signal(); //heisen tror den er i en etasje når den er mellom 2.
                set_floor(); 
            }
    	    elev_set_stop_lamp(0);
	        set_order();
	        if(findCollision()){
	            nextState = ARRIVED;
    	    	printf("noe fett");
	        	//stop_elevator();
		        //reset_direction(currentFloor); IKKE TESTET Å KOMMENTERE UT DENN E
                reset_order(currentFloor); //sletter alle bestillinger i denne etasjen dersom den blir kalt
		        print_floor();
		        start_timer();
		        //elev_set_door_open_lamp(1);		
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
	            //stop_elevator();
                print_floor();
                reset_order(currentFloor);
                start_timer();
                nextState = ARRIVED;
            }
            //Lagt inn denne siden sist. ikke prøvd
            else if(elev_get_floor_sensor_signal() == -1 && nextFloor == currentFloor){
               if(direction == 1){
                    drive_down();
                }
                else if(direction == 0){
                    drive_up(); 
                }
	    	    printf("%d", direction);
            }
            break;
        case ARRIVED:
	        stop_elevator();
	        elev_set_door_open_lamp(1);
            set_order(); 
            if(check_timer(3.0)){
                elev_set_door_open_lamp(0);
                nextState = TAKEORDER;
            }
	    break;
        case STOP_SIGNAL: //Klarer ikke kjøre ned til 2. får kun åpen dør signal. Opp går fint
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











