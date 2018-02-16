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
