#ifndef INC_ELEVATOR_H
#define INC_ELEVATOR_H
#include "../inc/order.h"
#include "../drivers/elevio.h"

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
    //Order order_list[20];

    OrderMatrix *queue[N_FLOORS][N_BUTTONS];
} Elevator;

Elevator* initialize_elevator();

#endif

