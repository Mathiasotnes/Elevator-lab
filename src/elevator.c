#include "../inc/elevator.h"
#include "../drivers/elevio.h"


Elevator* innit(){
    Elevator *elevator = 0;

    //TODO: Make instance of door -> ??put in elevator??
    /*
    Door* innitilize_door(3000);
    */

    for (int i = 0; i < 20; i++){
        elevator->order_list[i].valid = 0;
    }

    int currentFloor = elevio_floorSensor();
    while(currentFloor == -1){
        elevio_motorDirection(DIRN_UP);
        currentFloor = elevio_floorSensor();
    }

    elevator->floor = currentFloor;
    elevator->state = Neutral;
    return elevator;
}