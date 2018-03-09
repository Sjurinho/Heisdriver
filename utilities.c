#include "utilities.h"
#include "elev.h"
#include "timer.h"
#include "control.h"
#include <stdio.h>

/*---DEFINERER GLOBALE VARIABLER---*/
int order[N_FLOORS][3] = {{ 0 }};
    /* 2-indeks beskriver å BESTILLE heisen */
    /* 1-indeks beskriver heis OPP-knaoo */
    /* 0-indeks beskriver heis NED-knapp */
int orderSize = 0; //holder kontroll på størrelsen til ordre 

//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
    elev_set_door_open_lamp(1);
}
void drive(int direction){
    if(direction){
        elev_set_motor_direction(DIRN_UP);
    }
    else{	
        elev_set_motor_direction(DIRN_DOWN);
    }
}

void close_door(void){
    elev_set_door_open_lamp(0);
}

void stop_elevator(void){
    elev_set_motor_direction(DIRN_STOP);
}

//Setter heisen i definert tilstand
void initialize(void){ 
    while (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_UP); 
	}
	stop_elevator();
	close_door();
	set_floor();
}

//Tar seg av bestillingene
void set_order(void){
    for(int i = 0; i < N_FLOORS; i++){
        if(elev_get_button_signal(BUTTON_COMMAND, i)){
    		if(order[i][2] != 1){
        		order[i][2] = 1;
           		orderSize++; 
        		}
        elev_set_button_lamp(BUTTON_COMMAND, i, 1);
        }
        if( i < N_FLOORS-1){
        	if(elev_get_button_signal(BUTTON_CALL_UP, i)){
            	if(order[i][1] != 1){
                    order[i][1] = 1; 
                    orderSize++;
		        }
                elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
	        }
        }   
        if( i > 0){ //NED. dvs heisen i 2., 3. eller 4. etg.
	        if(elev_get_button_signal(BUTTON_CALL_DOWN, i)){
	            if(order[i][0] != 1){	
                    order[i][0] = 1; 
                    orderSize++;
            	}
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
            }   
	    }   
    }
}


int get_orderSize(){
    return orderSize;
}

int check_arrived(){
    return (currentState == nextState);
}
    
int get_floor(){ //Sjekker om noen av elementene er 1 for å finne bestillinger avhengig av retningen
    if (!direction){
	for (int i = 0; i < N_FLOORS; i++) {
            for (int j = 0; j < 3; j++) {
                if (order[i][j] == 1){
                    return i;
                }
            }
        }
    }
    else{
       	for (int i = N_FLOORS-1; i >= 0; i--) {
            for (int j = 0; j < 3; j++) {
                if (order[i][j] == 1){
                    return i;
        
                }
            }
        }
    }   
    return 0;
}


void reset_order(int floor){
    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    int onFloor = 0; //muligens litt forvirrende navn, men holder telling
    for (int i = 0; i <=2; i++){ // for alle de forskjellie knappene, opp, ned, bestilling  
        if(order[floor][i] == 1){ //slette alle eksisterende bestillinger som finnes i gitt etasje. Teller antall slettede bestillinger
            order[floor][i] = 0;
            onFloor++; 
        } 
   }
    //skrur av lys
    if(floor != 0){
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    if(floor != N_FLOORS-1){
        elev_set_button_lamp(BUTTON_CALL_UP,floor, 0); 
    }
    orderSize -= onFloor; //trekker antall slettede bestillinger fra orderSize
}

void set_floor(void){ //setter current floor)
	int tempFloor = elev_get_floor_sensor_signal();
	if(tempFloor >= 0){
		currentFloor = tempFloor;
		elev_set_floor_indicator(currentFloor);
    }
}

void set_stop(void){
	stop_elevator();
	elev_set_stop_lamp(elev_get_stop_signal());
	for(int i = 0; i < N_FLOORS; i++){
		reset_order(i);
	}
	if(elev_get_floor_sensor_signal() >= 0){
		open_door();
	}	
	
}

int find_collision(void){
    int tempFloor=elev_get_floor_sensor_signal();
    if (tempFloor!=-1){
        return (order[currentFloor][direction] || order[currentFloor][2]);
    }
   return 0;
}
