#include <time.h>

/*---DEFINING GLOBAL TIME VARIABLES AND FUNCTIONS---*/
time_t startValue;
time_t endValue;

//Starts the timer
void start_timer();

//Checks if the timer has reached seconds seconds
int check_timer(double seconds);
