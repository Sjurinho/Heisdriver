#include "statemachine.h"

void stateMachine(State next_state)
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
            for (int i = 0; i<N_FLOORS*2-2;i++){
                
            }
