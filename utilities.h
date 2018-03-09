/*---DEFINING GLOBAL VARIABLES---*/
int direction;
int currentFloor;
int nextFloor;

/*---FUNCTIONS USED IN STATEMACHINE---*/
void close_door(void);

void open_door(void);

void stop_elevator(void);

void initialize(void);

//Allows user to set order
void set_order(void);

//Sets CURRENT_FLOOR
void set_floor(void);

//Takes care of elevator stopping
void set_stop(void);

//Searches for orders in same direction. Returns true or false on floor
int find_collision(void);

int get_orderSize(void);

//Updates NEXT_FLOOR
int get_floor(void);

//Resets all orders on floor
void reset_order(int floor);

//Sets the motor direction
void drive(int direction);

