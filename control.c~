#include <stdio.h>
#include "control.h"
#include "door.h"
#include "utilities.h"
#include "elev.h"

enum State stateControl(enum State current_state){
     switch (current_state) {
        case INITIALIZE:
            if (!elev_init()){
                printf("Hardware is not initialized");
                next_state = FAIL;
        		break;
            }
            initialize(); 
            printFloor();
            next_state = TAKEORDER;
            break;
       case TAKEORDER:
            setOrder();
            if(get_order_size() !=  0){
                next_state = DRIVE;
            }
	        next_floor  = get_floor();
	        stop = 1;
            break;
        case DRIVE:
		    elev_set_stop_lamp(0);
	    	setOrder();
            if(elev_get_floor_sensor_signal() != -1){
                current_floor = elev_get_floor_sensor_signal(); //heisen tror den er i en etasje når den er mellom 2.
                set_floor(); 
            }
            if(current_floor > next_floor){
                drive_down();
                direction = -1; 
            }
            if(current_floor < next_floor){
                drive_up();
                direction = 1;
            }
            if(elev_get_floor_sensor_signal() == next_floor){
		        stop_elevator();
                printFloor();
                reset_order(current_floor);
                start_timer();
                elev_set_door_open_lamp(1);
                next_state = ARRIVED;
            }
            //Lagt inn denne siden sist. ikke prøvd
            if(elev_get_floor_sensor_signal() == -1 && next_floor == current_floor){
                if(direction == 1){
                   drive_down(); 
                }
                if(direction == -1){
                    drive_up(); 
                }
            }
            break;
        case ARRIVED:
            setOrder(); 
            if(check_timer(3.0)){
                elev_set_door_open_lamp(0);
                next_state = TAKEORDER;
            }
	        break;
        case STOP_SIGNAL: //Klarer ikke kjøre ned til 2. får kun åpen dør signal. Opp går fint
	        while (elev_get_stop_signal()){
		        set_stop();
		        start_timer();
		    }
    	    elev_set_stop_lamp(0);
	        if(elev_get_floor_sensor_signal()!=-1){
		        next_state=ARRIVED;
		        break;
		    }     
	        next_state=TAKEORDER;
	        break;      
        case FAIL:
            stop_elevator();
            printStop();
            printf("FAILURE");
            next_state = INITIALIZE;
    		break;
    	default:
    		break;
    }
	return next_state;
}











