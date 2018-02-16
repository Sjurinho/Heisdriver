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
        printf("Stopping\n");
}
