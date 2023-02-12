#include "../inc/fsm.h"
#include "../drivers/elevio.h"

void FSM_thread(Elevator* elevator, Door* door) {
    int floor_sensor = -1;
        switch (elevator->state)
        {
        case Neutral:
            //Function for determning the next state
            elevator->state = logic(elevator);
            // Display lights
            break;
        case StillUp:
            //Function for ddetermning the next state
            elevator->state = logic(elevator);
            // Display lights
            break;
        case StillDown:
            //Function for determning the next state
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
            // Christoffers Algoritme 3 :)
            break;
        case FloorhitDown:
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
            // Christoffers Algoritme 3 :)
            break;
        default:
            break;
        }
        
}
