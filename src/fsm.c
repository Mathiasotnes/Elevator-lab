#include "../inc/fsm.h"
#include "../driver/elevio.h"
#include "../inc/logic.h"
#include "../inc/door.h"
#include "../inc/order.h"
#include <stdio.h>

extern Door door;
extern Elevator elevator;

void FSM_thread() {
    int floor_sensor = -1;
    update_orders();
    update_door();
    printf("%s \r\n", statesToString[elevator.state]);
        switch (elevator.state)
        {

        case Neutral:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                if(elevio_floorSensor() != -1) {
                    open_door();
                }
                break;
            }
            elevio_stopLamp(0);
            elevio_motorDirection(DIRN_STOP);
            elevator.state = logic();
            break;


        case StillUp:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                open_door();
                break;
            }
            elevio_stopLamp(0);
            elevio_motorDirection(DIRN_STOP);
            if(door.state == Closed) {
                elevator.state = logic();
            }
            if(order_list[elevator.floor][BUTTON_HALL_UP] ||order_list[elevator.floor][BUTTON_CAB]) {
                complete_order(elevator.floor, BUTTON_HALL_UP);
                complete_order(elevator.floor, BUTTON_CAB);
                open_door();
            }
            
            break;


        case StillDown:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                open_door();
                break;
            }
            elevio_stopLamp(0);
            elevio_motorDirection(DIRN_STOP);
            if(door.state == Closed) {
                elevator.state = logic();
            }
            if(order_list[elevator.floor][BUTTON_HALL_DOWN] ||order_list[elevator.floor][BUTTON_CAB]) {
                complete_order(elevator.floor, BUTTON_HALL_DOWN);
                complete_order(elevator.floor, BUTTON_CAB);
                open_door();
            }
            break;


        case MovingUp:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                elevator.state = Neutral;
                break;
            }
            elevio_stopLamp(0);
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
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                elevator.state = Neutral;
                break;
            }
            elevio_stopLamp(0);
            elevio_motorDirection(DIRN_DOWN);
            floor_sensor = elevio_floorSensor();
            if(floor_sensor != -1) {
                elevator.floor = floor_sensor;
                elevator.state = FloorhitDown;
                elevio_floorIndicator(floor_sensor);
            }
            break;


        case FloorHitUp:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                open_door();
                break;
            }
            elevio_stopLamp(0);
            elevio_motorDirection(DIRN_STOP);
            if(floor_sensor != -1) {
                elevio_floorIndicator(floor_sensor);
            }
            elevator.state = logic();                               
            break;


        case FloorhitDown:
            if(elevio_stopButton()) {
                elevio_stopLamp(1);
                elevio_motorDirection(DIRN_STOP);
                clean_orders();
                open_door();
                break;
            }
            elevio_stopLamp(0);
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
