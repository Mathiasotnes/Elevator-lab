#include "../inc/fsm.h"
#include "../drivers/elevio.h"

void FSM_thread(Elevator* elevator) {
    int floor_sensor = -1;
        switch (elevator->state)
        {
        case Neutral:
            // Christoffers Algoritme 1 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
            // Display lights
            break;
        case StillUp:
            // Christoffers Algoritme 2 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
            // Display lights
            break;
        case StillDown:
            // Christoffers Algoritme 2 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
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
            // Christoffers Algoritme 3 :)
            break;
        case FloorhitDown:
            elevio_floorIndicator(floor_sensor);
            // Christoffers Algoritme 3 :)
            break;
        default:
            break;
        }
        
}