#include <stdio.h>
#include "utilities.h"
int stop;
int direction; //-1 ned, 1 opp
enum State { //Lager states som heisen kan være i
    INITIALIZE, TAKEORDER, DRIVE, STOP_SIGNAL, FAIL, ARRIVED};

enum State nextState; //hvilken state som er neste
enum State currentState; //hvilken state heisen er i

enum State stateControl(enum State currentState); //funksjon som styrer state til heisen 

