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
            update_door(door);
            elevator->state = logic(elevator);
            break;
        case StillUp:
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
