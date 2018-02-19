#include "statemachine.h"

void stateMachine(State next_state, elev_motor_direction_t dir)
int orders[0] = {0};    
switch (next_state){
        case initialize:
            if (!elev_init()){
                printf("HARDWARE IS NOT PROPERLY INITIALIzED!!!");
                next_state = FAIL;    
            }
            initialize();
            next_state = takeOrder;
            break;
        case takeOrder:
//finner første arbeidsoppgave og legger dette inn i en tabell
            for (int i = 0; i<N_FLOORS*2-2;i++){
                if (floorOrders[i] == 1){
                    orders[0] = int((i/2.0) + 0.5);//indeksering bare
                }
            }
            next_state = drive;
            break;
        case drive:
            elev_set_motor_direction(dir); 
            while (calculateFloor(orders[0]) < 0){
               if(findCollision(orders[0])){
                    next_state = door;
                    break;
                } 
            }
            break;
        case door:
            door_delay(3.0,dir);
            if (calculateFloor(orders[0])==0){
                next_state = takeOrder
            }
            else{next_state=drive}
            break;
