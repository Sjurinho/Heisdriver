#include "elev.h"
#include "statemachine.h"
#include "door.h"
#include "utilities.h"
#include <stdio.h>

int main() { 
    if(!elev_init()){
    return 1;
    }
//    initialize();
//    int current_floor = elev_get_floor_sensor_signal();
  //  printf(current_floor);
elev_set_motor_direction(DIRN_UP);

    elev_motor_direction_t Direction;
    Direction = DIRN_UP;
    while(1){
        switch(Direction){
	    case DIRN_DOWN:
	    if(elev_get_floor_sensor_signal() == 3){
		Direction = DIRN_DOWN;
		elev_set_motor_direction(Direction);
	    }
	    break;
            case DIRN_UP:
	    if(elev_get_floor_sensor_signal() == 0){
		Direction = DIRN_UP;

		elev_set_motor_direction(Direction);
	    }
	    break;
	    case DIRN_STOP:
		if(elev_get_stop_signal()){
		elev_set_motor_direction(Direction);
		}
		break; 
	}
	//elev_set_motor_direction(Direction);
    }
    return 0; 
}
