#include "../inc/order.h"

#ifndef INC_ELEVATOR_H
#define INC_ELEVATOR_H

/* Datatypes */
typedef enum ElevatorState {
    Neutral,
    StillUp,
    StillDown,
    MovingUp,
    MovingDown,
    FloorHitUp,
    FloorhitDown
} ElevatorState;

typedef struct Elevator{
    int floor;
    ElevatorState state;
    Order order_list[20];
} Elevator;

Elevator* initialize_elevator();

#endif

