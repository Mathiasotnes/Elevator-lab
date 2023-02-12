#include "../inc/elevator.h"
#include "../inc/interface.h"
#include "../inc/fsm.h"

Elevator* initialize_elevator() {
    Elevator* elevator =0;
    elevator->floor = 2; // Dette må løses, hvordan skal den boote opp?
    elevator->state = Neutral;
    // elevator->order_list = mange mange nullere :)
    return elevator;
}
#include "../drivers/elevio.h"


void innit(){
    //Initilizing door
    Door* door = initialize_door(3000);

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

    FSM_thread(elevator, door);
}
