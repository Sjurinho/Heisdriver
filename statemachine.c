#include "statemachine.h"

void stateMachine(State next_state)
    switch (next_state){
        case initialize:
            initialize();
            next_state = takeOrder;
            break;
