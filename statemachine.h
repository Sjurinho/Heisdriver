#include "utilites.h"
#include "elev.h"
enum States{
initialize, drive, openDoor, closeDoor, takeOrder
}State;
    
void stateMachine(void)
    switch (States){
        case initialize:
            initialize();
