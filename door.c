#include "elev.h"
#include "utilities.h"
#include "door.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>







void start_timer(){
	time(&start_value); // time() returns seconds since a pre-defined happening
}

int check_timer(double seconds){
	time(&end_value);
	if (difftime(end_value, start_value) >= seconds){
		return 1;
	
	}
	return 0;
}
