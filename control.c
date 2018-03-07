#include <stdio.h>
#include "control.h"
#include "timer.h"
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
	    delay(100); //dette er nødvendig for at heisen ikke skal åpnes to ganger i samme etasje. 
            if(get_order_size() !=  0){
                next_state = DRIVE;
            }
	    next_floor  = get_floor();
            break;
        case DRIVE:
            if(elev_get_floor_sensor_signal() != -1){
                current_floor = elev_get_floor_sensor_signal(); //heisen tror den er i en etasje når den er mellom 2.
                set_floor(); 
            }
    	    elev_set_stop_lamp(0);
	        setOrder();
	        if(findCollision()){
	            next_state = ARRIVED;
    	    	printf("noe fett");
                reset_order(current_floor); //sletter alle bestillinger i denne etasjen dersom den blir kalt
		        printFloor();
		        start_timer();
		        //elev_set_door_open_lamp(1);		
            }
            else if(current_floor > next_floor){
                drive_down();
                direction = 0; 
            }
            else if(current_floor < next_floor){
                drive_up();
                direction = 1;
            }
            else if(elev_get_floor_sensor_signal() == next_floor){
                printFloor();
                reset_order(current_floor);
                start_timer();
                next_state = ARRIVED;
            }
            //Lagt inn denne siden sist. ikke prøvd
            else if(elev_get_floor_sensor_signal() == -1 && next_floor == current_floor){
               if(direction == 1){
                    drive_down();
                }
                else if(direction == 0){
                    drive_up(); 
                }
            }
            break;
        case ARRIVED:
	        stop_elevator();
	        elev_set_door_open_lamp(1);
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











