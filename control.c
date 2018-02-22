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
            next_state = TAKEORDER;
            break;
        case TAKEORDER:
            setOrder();
            if(get_order_size() !=  0){
                next_state = DRIVE;
            }
            break;
        case DRIVE:
		elev_set_stop_lamp(0);
		setOrder();
            if(elev_get_stop_signal()){
                next_state = STOP_SIGNAL;
		break;
            }
            next_floor  = get_floor();
            if(elev_get_floor_sensor_signal() != -1){
                current_floor = elev_get_floor_sensor_signal();
                set_floor();
            }
            if(current_floor > next_floor){
                drive_down();
            }
            if(current_floor < next_floor){
                drive_up();
            }
            if(current_floor == next_floor){
		stop_elevator();
                reset_order(current_floor);
		door_delay(3.0);
                next_state = ARRIVED;
            }
            break;
        case ARRIVED:
            //legge inn en stopp her? 
            setOrder(); 
		close_door();
            next_state = TAKEORDER;
		break;
        case STOP_SIGNAL:
            if(elev_get_floor_sensor_signal()!= -1){
		printf("HER ER DET FEIL\n");
                set_stop();
                open_door();
                elev_set_door_open_lamp(1);
            }
            if(elev_get_stop_signal() == 0){
                timer(3.0);
                close_door();
                next_state = TAKEORDER;
            }
		break;
        case FAIL:
            stop_elevator();
            printf("FAILURE");
            next_state = INITIALIZE;
		break;
	default:
		break;
}
	return next_state;
}











