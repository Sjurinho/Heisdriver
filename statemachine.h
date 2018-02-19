#include "utilities.h"
#include "elev.h"
typedef enum States{
Initialize, drive, openDoor, closeDoor, takeOrder, fail
}State;

typedef enum SuperState {UP, DOWN}; 
