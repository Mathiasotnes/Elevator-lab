#ifndef INC_ELEVATOR_H
#define INC_ELEVATOR_H
#include "../inc/order.h"
#include "../driver/elevio.h"


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
} Elevator;

static const char * const statesToString[] = {
	[Neutral] = "Neutral",
	[StillUp] = "StillUp",
	[StillDown] = "StillDown",
	[MovingUp] = "MovingUp",
    [MovingDown] = "MovingDown",
    [FloorHitUp] = "FloorHitUp",
    [FloorhitDown] = "FloorhitDown"
};

extern Elevator elevator;

void initialize_elevator();

#endif

