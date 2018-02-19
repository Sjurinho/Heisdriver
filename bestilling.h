#include "utilities.h"
#include "elev.h"

extern int floorOrders[N_FLOORS*2 - 2]; 

int calculateFloor(int floorOrder);

void orderElevator(int floorOrdered);

int findCollision(int floorOrder);
