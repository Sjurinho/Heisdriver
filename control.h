#include <stdio.h>
#include "utilities.h"

/*---CONTAINS GLOBAL VARIABLES AND THE MAIN STATEMACHINE---*/

enum State NEXT_STATE; 
enum State CURRENT_STATE; 


enum State 
{ 
    INITIALIZE, TAKEORDER, DRIVE, STOP_SIGNAL, FAIL, ARRIVED
};


enum State stateControl(enum State currentState);

