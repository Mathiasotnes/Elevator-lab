#ifndef INC_ELEVATOR_H
#define INC_ELEVATOR_H
#include "../inc/order.h"

typedef enum {
    Neutral,
    StillUp,
    StillDown,
    MovingUp,
    MovingDown,
    FloorHitUp,
    FloorhitDown
} ElevatorState;

/**
 * This is purly for debugging pruposes
 * and can be deleted in final verison
 */
/*
const char * const to_state_str[] = {
    [Neutral] = "Neutral", 
    [StillUp] = "StillUp", 
    [StillDown] = "StillDown", 
    [MovingUp] = "MovingUp", 
    [MovingDown] = "MovingDown",
    [FloorHitUp] = "FloorHitUp",
    [FloorhitDown] = "FloorHitDown",
};
*/

typedef struct Elevator{
    int floor;
    ElevatorState state;
    Order order_list[20];
} Elevator;

#endif

