#include "statemachine.h"

void stateMachine(State next_state)
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
                    orders[0] = int((i/2.0) + 0.5);
                }
            }
            next_state = drive;
            break;
