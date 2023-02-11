#include "../inc/fsm.h"
#include "../drivers/elevio.h"
#include "../inc/logic.h"

void FSM_thread(Elevator* elevator) {
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
                /* Oppdater floor indicator */
                break;
            }
            break;
        case MovingDown:
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator->floor = floor_sensor;
                elevator->state = FloorhitDown;
                /* Oppdater floor indicator */
            }
            break;
        case FloorHitUp:
            elevio_floorIndicator(floor_sensor);
            //Function for determning the next state
            elevator->state = logic(elevator);
            break;
        case FloorhitDown:
            elevio_floorIndicator(floor_sensor);
            //Function for determning the next state
            elevator->state = logic(elevator);
            break;
        default:
            break;
        }
        
}
