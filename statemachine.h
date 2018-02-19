#include "utilities.h"
#include "elev.h"
#include "bestilling.h"
#include <stdlib.h>
typedef enum States{
INITIALIZE, DRIVE, DOOR, TAKEORDER, FAIL
}State;
void stateMachine(State next_state, elev_motor_direction_t dir);
