/*---DEFINING GLOBAL VARIABLES---*/
int DIRECTION_UP;
int CURRENT_FLOOR;
int NEXT_FLOOR;

/*---FUNCTIONS USED IN STATEMACHINE---*/

void stop_elevator(void);

void initialize(void);

//Allows user to set order
void set_order(void);

//Sets CURRENT_FLOOR
void set_floor(void);

//Takes care of elevator stopping
void set_stop(void);

//Updates NEXT_FLOOR depending on direction
int get_floor(void);

//Resets all orders on floor
void reset_order(int floor);

//Sets the direction variable
void set_direction(int lastDir);

//Decides best path and drives there depending on the elevators last direction, also updates and returns last direction 
int drive_to_floor(int lastDir);

//Takes care of stop
void stopping(void);