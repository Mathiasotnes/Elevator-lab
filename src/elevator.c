#include "../inc/elevator.h"
#include "../inc/interface.h"
#include "../inc/fsm.h"
#include "../drivers/elevio.h"

Elevator* initialize_elevator(){

    Elevator *elevator = 0;

    //Making empty order list
    for (int i = 0; i < 20; i++){
        elevator->order_list[i].valid = 0;
    }

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
