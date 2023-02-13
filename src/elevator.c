#include "../inc/elevator.h"
#include "../inc/interface.h"
#include "../inc/fsm.h"
#include "../drivers/elevio.h"

Elevator* initialize_elevator(){

    Elevator *elevator = 0;

    //Intilizing queue
    **elevator->queue = initialize_order_list(); //Not to sure about this ...

    //Defining floor
    int currentFloor = elevio_floorSensor();
    while(currentFloor == -1){
        elevio_motorDirection(DIRN_UP);
        currentFloor = elevio_floorSensor();
    }

    elevator->floor = currentFloor;
    elevator->state = Neutral;

    return elevator;
}
