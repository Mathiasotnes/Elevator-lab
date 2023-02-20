#include "../inc/elevator.h"
#include "../inc/door.h"
#include "../inc/fsm.h"
#include "../driver/elevio.h"

void initialize_elevator(){

    //Defining floor
    int currentFloor = elevio_floorSensor();
    while(currentFloor == -1){
        elevio_motorDirection(DIRN_UP);
        currentFloor = elevio_floorSensor();
    }

    elevator.floor = currentFloor;
    elevator.state = Neutral;
}
