#include <stdio.h>
#include "utilities.h"
#include "elev.h"

void initialize(void){ //Setter heisen i definert tilstand
        while (elev_get_floor_sensor_signal()<0 && elev_get_stop_signal != 1){ //stoppknappen ignoreres ikke, men det gjør bestillingsknappene siden vi må vite hvor vi er.
                drive_up(); //kjører opp til nærmeste etasje, trenger ikke tenke på kantene ettersom dette er en precondition
        }
        stop_elevator(); //stopper i etasjen.
}
