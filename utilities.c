#include "elev.h"
#include "control.h"
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
        elev_set_stop_lamp(1);
        printf("Stopping");
}

void initialize(void){ //Setter heisen i definert tilstand
        while (elev_get_floor_sensor_signal() == -1){//ignorerer stopp og bestilling 
                elev_set_motor_direction(DIRN_UP); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondit
	}
        elev_set_motor_direction(DIRN_STOP); //stopper i etasjen.
}


void light_floor(void){
    if (elev_get_floor_sensor_signal() >= 0){
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
    }
}

int order[N_FLOORS][3] = { 0 }; //initialiserer en 2D-liste. N_FLOOR etasjer og 3 forskjellige typer knapper
    /* 0-indeks beskriver å BESTILLE heisen */
    /* 1-indeks beskriver heis OPP-knaoo */
    /* 2-indeks beskriver heis NED-knapp */

 int order_size = 0; //variabel for kontroll over str på order. 
 


void setOrder(void){
    for(int i = 0; i < N_FLOORS; i++){
        if(elev_get_button_signal(BUTTON_COMMAND, i) > 0){ //BESTILLE
            order[i][0] = 1;
            order_size++;

            elev_set_button_lamp(BUTTON_COMMAND, i, 1);
        }
        if( i < N_FLOORS-1){//OPP. dvs heisen i 1. etg, 2 etg. eller 3. etg
            order[i][1] = 1; 
            order_size++;

            elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
        }
        if( i > 0){ //NED. dvs heisen i 2., 3. eller 4. etg.
            order[i][2] = 1; 
            order_size++;

            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
        }
    }
}

int get_order_size(){
    return order_size;
}

int checkArrived(){
    return (current_state == next_state);
}
    
int get_floor(){ //Sjekker om noen av elementene er 1 for å finne etasje 
    for (i = 0; i < N_FLOORS; i++) {
        for (j = 0; j < 3; j++) {
            if (order[i][j] == 1){
                return i;
            }
        }
    }
    return 0;
}

void reset_order(int floor){
    elev_set_button_lamp(BUTTON_COMMAND, current_floor, 0);
    int onFloor = 0;
    for (i = 0; i < 3; i++) {
        if(order[current_floor][i] == 1){
            order[current_floo][i] = 0;
            onFloor++; 
        } 
    }
    if(current_floor != 0){
        elev_set_button_lamp(BUTTON_CALL_DOWN, current_floor, 0);
    }
    if(current_floor != N_FLOORS){
        elev_set_button_lamp(BUTTON_CALL_UP, current_floor, 0); 
    }
    order_size -= onFloor;
}
















