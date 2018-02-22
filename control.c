#include <stdio.h>
#include "door.h"
#include "utilities.h"
#include "elev.h"

enum State stateControl(enum State current_state){
    switch (next_state) {
        case INITIALIZE:
            if (!elev_init()){
                printf("Hardware is not initialized");
                next_state = FAIL;
            }
            initialize(); 
            next_state = TAKEORDER;
            break;
        case TAKEORDER:
            setOrder();
            if(get_order_size() > 0){
                next_state = DRIVE;
            }
            break;
        case DRIVE:
            if(elev_get_stop_signal){
                next_state = STOP_SIGNAL;
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
                next_state = ARRIVVED; 
                reset_order(current_floor);
                next_state = ARRIVED;
            }
            break;
        case ARRIVED:
            door_delay(3.0); 
            //legge inn en stopp her? 
            setOrder(); 
            next_state = TAKEORDER;
        case STOP_SIGNAL:
            if(elev_get_floor_sensor_signal() != -1){
                set_stop();
                open_door();
                elev_set_door_open_lamp(1);
            }
            if(elev_get_stop_signal() == 0){
                timer(3.0);
                close_door();
                next_state = TAKEORDER;
            }
        case FAIL:
            stop_elevator();
            printf("FAILURE");
            next_state = INITIALIZE;
    }

}











