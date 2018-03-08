int direction;
int currentFloor;
int nextFloor;

void close_door(void);

void open_door(void);

void drive_up(void);

void drive_down(void);

void stop_elevator(void);

void initialize(void);

void set_order(void);

void set_floor(void);

void set_stop(void);

void print_order(void);

void print_floor(void);

void print_stop(void);

int find_collision(void);

void reset_direction(int floor);

int get_orderSize(void);

int get_floor(void);

void reset_order(int floor);

void calculate_path(void);

void update_direction(int floor);

void drive(int direction);

int elevator_is_below_sensor(int direction);
