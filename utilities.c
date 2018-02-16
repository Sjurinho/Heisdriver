<<<<<<< HEAD
#include "elev.h"
#include <stdio.h>
//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
        elev_set_door_lamp(1);
        printf("The door is open");
}

void close_door(void){
        elev_set_door_lamp(0);
        printf("The door is closed");
}

void drive_up(void){
        elev_set_motor_direction(UP);
        printf("Going up");
}

void drive_down(void){
        elev_set_motor_direction(DOWN);
        printf("Going down");
}

void stop_elevator(void){
        elev_set_motor_direction(STOP);
        printf("Stopping");
}

void initialize(void){ //Setter heisen i definert tilstand
        while (elev_get_floor_sensor_signal()<0){//ignorerer stopp og bestilling 
                drive_up(); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondition
        }
        stop_elevator(); //stopper i etasjen.
}
=======
#include "elev.h"
//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
        elev_set_door_lamp(1);
        printf("The door is open");
}

void close_door(void){
        elev_set_door_lamp(0);
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
>>>>>>> origin
