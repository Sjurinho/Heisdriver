#include <time.h>

/*---DEFINING GLOBAL TIME VARIABLES AND FUNCTIONS---*/
time_t startValue;
time_t endValue;

//starts the timer
void start_timer();

//checks if the timer has reached seconds seconds
int check_timer(double seconds);
