#include "../inc/fsm.h"
#include "../driver/elevio.h"
#include "../inc/logic.h"
#include "../inc/door.h"
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
            update_door();
            if(door.state == Closed) {
                elevator.state = logic();
            }
            complete_order(elevator.floor, BUTTON_HALL_UP);
            complete_order(elevator.floor, BUTTON_CAB);
            break;


        case StillDown:
            elevio_motorDirection(DIRN_STOP);
            update_door();
            if(door.state == Closed) {
                elevator.state = logic();
            }
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
            if(elevator.state == StillUp) {
                open_door();                    // open_door() er nå en entry-funksjon til Still-states, 
            }                                   // og skal lukkes etter 3 sekunder derfra.
            break;


        case FloorhitDown:
            update_door();
            elevio_motorDirection(DIRN_STOP);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
            elevator.state = logic();
            if(elevator.state == StillDown) {
                open_door();
            }
            break;


        default:
            elevio_motorDirection(DIRN_STOP);
            printf("Elevator has been set in service mode, please use stairs!\n");
            break;
        }
        
}
