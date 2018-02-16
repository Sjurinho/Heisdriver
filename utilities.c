#include "elev.h"
#include <stdio.h>
//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
        elev_set_door_open_lamp(1);
        printf("The door is open\n");
}

void close_door(void){
        elev_set_door_open_lamp(0);
        printf("The door is closed\n");
}

void drive_up(void){
        elev_set_motor_direction(DIRN_UP);
        printf("Going up\n");
}

void drive_down(void){
        elev_set_motor_direction(DIRN_DOWN);
        printf("Going down\n");
}

void stop_elevator(void){
        elev_set_motor_direction(DIRN_STOP);
        printf("Stopping \n");
}

void initialize(void){ //Setter heisen i definert tilstand
        while (elev_get_floor_sensor_signal()<0){//ignorerer stopp og bestilling 
                drive_up(); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondition
        }
        stop_elevator(); //stopper i etasjen.
}
