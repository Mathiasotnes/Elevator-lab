#include "../inc/interface.h"

/* Timeout in ms */
Door* initialize_door(int timeout) {
    Door *door;
    door->state = Open;
    door->timeout = timeout;
    door->start_time = clock();
    door->elapsed_time = clock();
    return door;
}

void update_door(Door *door) {
    int elapsed_time_ms = (door->elapsed_time - door->start_time) * 1000 / CLOCKS_PER_SEC;
    switch (door->state)
    {
    case Open:
        elevio_doorOpenLamp(1);
        if(elapsed_time_ms > door->timeout) {
            door->state = Closing;
        }
        else if(elevio_stopButton()) {
            door->start_time = clock();
            door->elapsed_time = clock();
        }
        else {
            door->elapsed_time = clock();
        }
        break;
    case Closing:
        if(elevio_obstruction()) {
            door->state = Open;
            door->start_time = clock();
            door->elapsed_time = clock();
            elevio_doorOpenLamp(1);
        }
        else if(elevio_stopButton()) {
            door->start_time = clock();
            door->elapsed_time = clock();
        }
        else {
            door->state = Closed;
        }
        break;
    case Closed:
        /* Trenger et åpningssignal for å gå i state "Open" og resette klokkene */
        /* Bare sett instansen av door->state til Open, */
        /* Da vil automatisk lyset skrus på og timer starte */
        elevio_doorOpenLamp(0);
        break;
    default:
        break;
    }
}


