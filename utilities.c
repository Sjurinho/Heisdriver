#include "utilities.h"
#include "elev.h"
#include "timer.h"
#include "control.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---Defining 2D-array that contains orders---*/
int order[N_FLOORS][3] = {{ 0 }};
    /* 0-index describes elevator DOWN button */
    /* 1-index describes elevator UP button*/
    /* 2-index describes INSIDE button */

 //keeps track of how many orders that are currently active
int orderSize = 0;


void open_door(void){
    elev_set_door_open_lamp(1);
}

void close_door(void){
    elev_set_door_open_lamp(0);
}

void stop_elevator(void){
    elev_set_motor_direction(DIRN_STOP);
}

void drive(int DIRECTION_UP){
    if(DIRECTION_UP){
        elev_set_motor_direction(DIRN_UP);
    }
    else{	
        elev_set_motor_direction(DIRN_DOWN);
    }
}


//Initializes the elevator
void initialize(void){ 
    while (elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(DIRN_UP); 
	}
	stop_elevator();
	close_door();
	set_floor();
}

//Controlling the different orders
void set_order(void){
    for(int i = 0; i < N_FLOORS; i++){ 
        if(elev_get_button_signal(BUTTON_COMMAND, i)){ //Inside buttons
    		if(order[i][2] != 1){
        		order[i][2] = 1;
           		orderSize++; 
        		}
        elev_set_button_lamp(BUTTON_COMMAND, i, 1);
        }
        if( i < N_FLOORS-1){ //Up buttons
        	if(elev_get_button_signal(BUTTON_CALL_UP, i)){
            	if(order[i][1] != 1){
                    order[i][1] = 1; 
                    orderSize++;
		        }
                elev_set_button_lamp(BUTTON_CALL_UP, i, 1);
	        }
        }   
        if( i > 0){ //Down buttons
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

    
/*--- Depending on which direction the elevator is going, decides the next floor.---*/
int get_floor(){ 
    if (!DIRECTION_UP){
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

/*--- Resets all orders and turn of lights on the floor if called. Updates orderSize ---*/
void reset_order(int floor){
    elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    int onFloor = 0; 
    for (int i = 0; i <=2; i++){ 
        if(order[floor][i] == 1){
            order[floor][i] = 0;
            onFloor++; 
        } 
    }
    if(floor != 0){
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    if(floor != N_FLOORS-1){
        elev_set_button_lamp(BUTTON_CALL_UP,floor, 0); 
    }
    orderSize -= onFloor; 
}

void set_floor(void){
	if(elev_get_floor_sensor_signal() >= 0){
		CURRENT_FLOOR = elev_get_floor_sensor_signal();
		elev_set_floor_indicator(CURRENT_FLOOR);
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
        return (order[CURRENT_FLOOR][DIRECTION_UP] || order[CURRENT_FLOOR][2]);
    }
   return 0;
}

void set_direction(int lastDir){
	set_order();
	if(get_orderSize() !=  0){
        NEXT_STATE = DRIVE;
        NEXT_FLOOR  = get_floor();
        if(CURRENT_FLOOR > NEXT_FLOOR){
            DIRECTION_UP = 0;
        }
        else if(CURRENT_FLOOR < NEXT_FLOOR){
            DIRECTION_UP = 1;
        }
        else if(elev_get_floor_sensor_signal() == -1 && NEXT_FLOOR==CURRENT_FLOOR){
            if (lastDir == 0){
                DIRECTION_UP = 1;
            }
            else if(lastDir == 1){
                DIRECTION_UP = 0;
            } 
        } 
    }
}

int drive_to_floor(int lastDir){
	set_floor(); 
	if (elev_get_floor_sensor_signal() == -1 && NEXT_FLOOR != CURRENT_FLOOR){
		lastDir = DIRECTION_UP;
	}
	elev_set_stop_lamp(0);
    set_order();
    drive(DIRECTION_UP);
	if(find_collision()){
		NEXT_STATE = ARRIVED;
	    start_timer();
    }
    else if(elev_get_floor_sensor_signal() == NEXT_FLOOR){
    	start_timer();
    	NEXT_STATE = ARRIVED;
    }
    return lastDir;
}

void stopping(void){
	while (elev_get_stop_signal()){
		set_stop();
		start_timer();
	}
	elev_set_stop_lamp(0);   
}
