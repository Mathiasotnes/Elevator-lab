#include "../inc/fsm.h"
#include "../drivers/elevio.h"

void FSM_thread(Elevator* elevator, Door* door) {
    int floor_sensor = -1;
        switch (elevator->state)
        {
        case Neutral:
            update_door(door);                              // Disse to kan kuttes ut i flere 
            if(floor_sensor != -1) {                        // states for å redusere runtime
                elevio_floorIndicator(floor_sensor);        // men har de med for redundancy for nå.
            }
            // Christoffers Algoritme 1 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
            // Display lights
            break;
        case StillUp:
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
            // Christoffers Algoritme 2 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
            // Display lights
            break;
        case StillDown:
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
            // Christoffers Algoritme 2 :)
            // Algoritmen bestemmer hvilke state vi skal inn i.
            // Display lights
            break;
        case MovingUp:
            update_door(door);
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