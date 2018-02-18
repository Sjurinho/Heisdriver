#include "bestilling.h"

//Tabell med boolske verdier som representerer bestillinger
int floorOrders[N_FLOORS*2-2]={0};
//returnerer antall etasjer mellom nåværende etasje og bestilt etasje
int calculateFloor(int floorOrder){
    return floorOrder - elev_get_floor_signal();
}
//setter knappens plass i tabellen til true
void orderElevator(int floorOrder){
    floorOrders[floorOrder*2-elev_button_type_t]=1;
}
//returnerer true hvis det er en kollisjon i etasjen
int findCollision(int floorOrder){
    int currentFloor=elev_get_floor_sensor_signal()
    int dir = elev_motor_direction_t < 0; //0 hvis dir = OPP, 1 hvis dir = NED
    return floorOrders[currentFloor*2-dir] && currentfloor != -1; //Kommer aldri til å måtte sjekke for topp og bunnetasje, husk på å kalle i rett rekkefølge!  
}


