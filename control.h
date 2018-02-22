#include <stdio.h>
#include "utilities.h"

enum State { //Lager states som heisen kan være i
    INITIALIZE, TAKEORDER, DRIVE, STOP_SIGNAL, FAIL, ARRIVED};

enum State next_state; //hvilken state som er neste
enum State current_state; //hvilken state heisen er i

enum State stateControl(enum State current_state); //funksjon som styrer state til heisen 

int get_order_size();
int get_floor();
void reset_order(int floor);
