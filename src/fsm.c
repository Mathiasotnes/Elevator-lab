#include "../inc/fsm.h"
#include "../drivers/elevio.h"
#include "../inc/logic.h"
#include "../inc/interface.h"
#include <stdio.h>

void FSM_thread(Elevator* elevator, Door* door) {
    int floor_sensor = -1;
        switch (elevator->state)
        {
        case Neutral:
            //Function for determining the next state
            elevator->state = logic(elevator);
            // Display lights
            break;
        case StillUp:
            //Function for determining the next state
            elevator->state = logic(elevator);
            // Display lights
            break;
        case StillDown:
            //Function for determining the next state
            elevator->state = logic(elevator);
            // Display lights
            break;
        case MovingUp:
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator->floor = floor_sensor;
                elevator->state = FloorHitUp;
                elevio_floorIndicator(floor_sensor);
                break;
            }
            break;
        case MovingDown:
            update_door(door);
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator->floor = floor_sensor;
                elevator->state = FloorhitDown;
                elevio_floorIndicator(floor_sensor);
            }
            break;
        case FloorHitUp:
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
             elevator->state = logic(elevator);
            break;
        case FloorhitDown:
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
             elevator->state = logic(elevator);
            break;
        default:
            printf("Elevator has been set in service mode, please use stairs!\n");
            break;
        }
        
}
