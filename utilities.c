#include "utilities.h"
#include "elev.h"
#include "control.h"
#include <stdio.h>
//forenkling av alle funksjonsnavn + printer til konsoll hva som skjer
void open_door(void){
        elev_set_door_open_lamp(1);
//        printf("The door is open");
}

void close_door(void){
        elev_set_door_open_lamp(0);
  //      printf("The door is closed");
}

void drive_up(void){
        elev_set_motor_direction(DIRN_UP);
    //    printf("Going up");
}

void drive_down(void){
        elev_set_motor_direction(DIRN_DOWN);
      //  printf("Going down");
}

void stop_elevator(void){
        elev_set_motor_direction(DIRN_STOP);
//        elev_set_stop_lamp(1);
       // printf("Stopping");
}

void initialize(void){ //Setter heisen i definert tilstand
    while (elev_get_floor_sensor_signal() == -1){//ignorerer stopp og bestilling 
        elev_set_motor_direction(DIRN_UP); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondit
	}
	stop_elevator();
	close_door();
	set_floor();
}


void light_floor(void){
    if (elev_get_floor_sensor_signal() >= 0){
        elev_set_floor_indicator(elev_get_floor_sensor_signal());
    }
}

//order og order_size er globale variabler
int order[N_FLOORS][3] = {{ 0 }}; //initialiserer en 2D-liste. N_FLOOR etasjer og 3 forskjellige typer knapper
    /* 2-indeks beskriver å BESTILLE heisen */
    /* 1-indeks beskriver heis OPP-knaoo */
    /* 0-indeks beskriver heis NED-knapp */
 int order_size = 0; //variabel for kontroll over str på order. 
 

//Er dette en god løsning for bestilling (med forløkka)
void setOrder(void){
//	if(elev_get_floor_sensor_signal() >= 0){
    for(int i = 0; i < N_FLOORS; i++){
        if(elev_get_button_signal(BUTTON_COMMAND, i)){ //BESTILLE, dvs indeksen er 2
    		if(order[i][2] != 1){
        		order[i][2] = 1;
           		order_size++; //holder kontroll på størrelsen til ordre 
        		}
        elev_set_button_lamp(BUTTON_COMMAND, i, 1);
        }
        if( i < N_FLOORS-1){//OPP. dvs heisen i 1. etg, 2 etg. eller 3. etg
        	if(elev_get_button_signal(BUTTON_CALL_UP, i)){
            	if(order[i][1] != 1){
                    order[i][1] = 1; 
                    order_size++;
		        }
                elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
	        }
        }   
        if( i > 0){ //NED. dvs heisen i 2., 3. eller 4. etg.
	        if(elev_get_button_signal(BUTTON_CALL_DOWN, i)){
	            if(order[i][0] != 1){	
                    order[i][0] = 1; 
                    order_size++;
            	}
            elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
            }   
	    }   
    }
}


int get_order_size(){
    return order_size;
}

int checkArrived(){
    return (current_state == next_state);
}
    
int get_floor(){ //Sjekker om noen av elementene er 1 for å finne bestillinger  
    for (int i = 0; i < N_FLOORS; i++) {
        for (int j = 0; j < 3; j++) {
            if (order[i][j] == 1){
                return i;
            }
        }
    }
    return 0;
}

void reset_order(int floor){
    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    int onFloor = 0; //muligens litt forvirrende navn, men holder telling
    for (int i = 0; i <=2; i++){ // for alle knappene  
        if(order[floor][i] == 1){ //slette alle eksisterende bestillinger som finnes i gitt etasje. Teller antall slettede bestillinger
            order[floor][i] = 0;
            onFloor++; 
        } 
    }
    if(floor != 0){ //skrur av lys
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    if(floor != N_FLOORS-1){
        elev_set_button_lamp(BUTTON_CALL_UP,floor, 0); 
    }
    order_size -= onFloor; //trekker antall slettede bestillinger fra order_size
}

void set_floor(void){ //straight up tatt fra hermaninho, setter floor_indicator og skriver ut current floor. Noe galt med denne funksjonen (eller kallet) er at den blir kalt i en evig løkke (skriver ut hele tiden)
	int temp_floor = elev_get_floor_sensor_signal();
	if(temp_floor >= 0){
		current_floor = temp_floor;
		elev_set_floor_indicator(current_floor);
    }
}


void set_stop(void){
	stop_elevator();
	elev_set_stop_lamp(elev_get_stop_signal());
	for(int i= 0; i< N_FLOORS - 1; i++){
		reset_order(i);
	}
	if(elev_get_floor_sensor_signal() >= 0){
		open_door();
	}	
}





void printOrder(void){
	for (int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++){
			printf("%d ", order[i][j]);
			}
		printf("\n");
	}
}

void printFloor(void){
    printf("current floor is: ");
	printf("%d", current_floor);
    printf("\n");
	
}

void printStop(void){
    printf("Motor stopped!");
    if( elev_get_stop_signal()){
        printf("Stop light enabled!");
    }
    printFloor();
}
