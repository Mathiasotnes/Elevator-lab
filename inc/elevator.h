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

static const char * const statesToString[] = {
	[Neutral] = "Neutral",
	[StillUp] = "StillUp",
	[StillDown] = "StillDown",
	[MovingUp] = "MovingUp",
    [MovingDown] = "MovingDown",
    [FloorHitUp] = "FloorHitUp",
    [FloorhitDown] = "FloorhitDown"
};

typedef struct Elevator{
    int floor;
    ElevatorState state;
    //Order order_list[20];

    OrderMatrix *queue;
} Elevator;

Elevator* initialize_elevator();

#endif

