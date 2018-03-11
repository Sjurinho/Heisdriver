#include "timer.h"
#include <time.h>

void start_timer(){
	time(&startValue); //time() returns seconds since a pre-defined happening
}

int check_timer(double seconds){
	time(&endValue);
	if (difftime(endValue, startValue) >= seconds){
		return 1;
	}
	return 0;
}
