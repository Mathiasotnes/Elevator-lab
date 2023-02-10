#include "order.h"

typedef enum {
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

ElevatorState floorHit(Elevator *heisen);

ElevatorState stillLogic(Elevator *heisen);

ElevatorState neutralLogic(Elevator *heisen),

