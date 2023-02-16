#include "../inc/fsm.h"
#include "../drivers/elevio.h"
#include "../inc/logic.h"
#include "../inc/interface.h"
#include <stdio.h>

void FSM_thread(Elevator* elevator, Door* door) {
    int floor_sensor = -1;
    update_orders(elevator->queue);
        switch (elevator->state)
        {
        case Neutral:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
            update_door(door);
            elevator->state = logic(elevator);
            break;
        case StillUp:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
            if(door->state == Closing) {
                elevator->state = logic(elevator);
                break;
            }
            if(door->state == Closed) {
                open_door(door);
            }
            update_door(door);
            complete_order(elevator->queue, elevator->floor, BUTTON_HALL_DOWN);
            complete_order(elevator->queue, elevator->floor, BUTTON_CAB);
            break;
        case StillDown:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
            if(door->state == Closing) {
                elevator->state = logic(elevator);
                break;
            }
            door->state = Open;
            update_door(door);
            complete_order(elevator->queue, elevator->floor, BUTTON_HALL_DOWN);
            complete_order(elevator->queue, elevator->floor, BUTTON_CAB);
            break;
        case MovingUp:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
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
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
            update_door(door);
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator->floor = floor_sensor;
                elevator->state = FloorhitDown;
                elevio_floorIndicator(floor_sensor);
            }
            break;
        case FloorHitUp:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
            update_door(door);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
             elevator->state = logic(elevator);
            break;
        case FloorhitDown:
            printf("Elevator is currently in: %s \n", statesToString[elevator->state]);
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
