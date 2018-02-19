#include "elev.h"
#include <stdio.h>
//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
        elev_set_door_open_lamp(1);
        printf("The door is open");
}

void close_door(void){
        elev_set_door_open_lamp(0);
        printf("The door is closed");
}

void drive_up(void){
        elev_set_motor_direction(DIRN_UP);
        printf("Going up");
}

void drive_down(void){
        elev_set_motor_direction(DIRN_DOWN);
        printf("Going down");
}

void stop_elevator(void){
        elev_set_motor_direction(DIRN_STOP);
        printf("Stopping");
}

void initialize(void){ //Setter heisen i definert tilstand
        while (elev_get_floor_sensor_signal()== -1){//ignorerer stopp og bestilling 
		printf("LOOOP");
                elev_set_motor_direction(DIRN_UP); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondit
		}
        }
        stop_elevator(); //stopper i etasjen.
}


void light_floor(void){
    if (elev_get_floor_sensor_signal() >= 0){
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
    }
}
