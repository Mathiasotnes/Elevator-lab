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

struct Elevator{
    int floor;
    ElevatorState state;
    Order order_list[20];
};

