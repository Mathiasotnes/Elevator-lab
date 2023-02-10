#include "../inc/elevator.h"

Elevator* initialize_elevator() {
    Elevator* elevator;
    elevator->floor = 2; // Dette må løses, hvordan skal den boote opp?
    elevator->state = Neutral;
    // elevator->order_list = mange mange nullere :)
    return elevator;
}
