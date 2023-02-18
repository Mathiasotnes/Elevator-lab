#include "../inc/fsm.h"
#include "../driver/elevio.h"
#include "../inc/logic.h"
#include "../inc/interface.h"
#include <stdio.h>

extern Door door;
extern Elevator elevator;

void FSM_thread() {
    int floor_sensor = -1;
    update_orders();
        switch (elevator.state)
        {
        case Neutral:
            elevio_motorDirection(DIRN_STOP);
            update_door();
            elevator.state = logic();
            break;
        case StillUp:
            elevio_motorDirection(DIRN_STOP);
            if(door.state == Closing) {
                elevator.state = logic();
                break;
            }
            if(door.state == Closed) {
                open_door();
            }
            update_door();
            complete_order(elevator.floor, BUTTON_HALL_DOWN); //<- Should be HALL_UP??
            complete_order(elevator.floor, BUTTON_CAB);
            break;
        case StillDown:
            elevio_motorDirection(DIRN_STOP);
            if(door.state == Closing) {
                elevator.state = logic();
                break;
            }
            door.state = Open;
            update_door();
            complete_order(elevator.floor, BUTTON_HALL_DOWN);
            complete_order(elevator.floor, BUTTON_CAB);
            break;
        case MovingUp:
            update_door();
            elevio_motorDirection(DIRN_UP);
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator.floor = floor_sensor;
                elevator.state = FloorHitUp;
                elevio_floorIndicator(floor_sensor);
                break;
            }
            break;
        case MovingDown:
            update_door();
            elevio_motorDirection(DIRN_DOWN);
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator.floor = floor_sensor;
                elevator.state = FloorhitDown;
                elevio_floorIndicator(floor_sensor);
            }
            break;
        case FloorHitUp:
            update_door();
            elevio_motorDirection(DIRN_STOP);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
             elevator.state = logic();
            break;
        case FloorhitDown:
            update_door();
            elevio_motorDirection(DIRN_STOP);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
             elevator.state = logic();
            break;
        default:
            elevio_motorDirection(DIRN_STOP);
            printf("Elevator has been set in service mode, please use stairs!\n");
            break;
        }
        
}
