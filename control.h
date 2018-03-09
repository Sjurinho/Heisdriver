#include <stdio.h>
#include "utilities.h"

/*---CONTAINS GLOBAL VARIABLES AND THE MAIN STATEMACHINE---*/

int direction; //0 down, 1 up
enum State nextState; 
enum State currentState; 


enum State 
{ 
    INITIALIZE, TAKEORDER, DRIVE, STOP_SIGNAL, FAIL, ARRIVED
};


enum State stateControl(enum State currentState);

