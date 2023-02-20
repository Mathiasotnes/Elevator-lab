#include "../inc/door.h"

/* Timeout in ms */
void initialize_door(int timeout) {
    door.state = Open;
    door.timeout = timeout;
    door.start_time = time(NULL);
    door.elapsed_time = time(NULL);
}

void open_door() {
    door.state = Open;
    door.start_time = time(NULL);
    door.elapsed_time = time(NULL);
}

void update_door() {
    int elapsed_time_ms = (door.elapsed_time - door.start_time) * 1000 / CLOCKS_PER_SEC;
    switch (door.state)
    {
        
    case Open:
        elevio_doorOpenLamp(1);
        if(elevio_stopButton() || elevio_obstruction()) {
            door.start_time = time(NULL);
            door.elapsed_time = time(NULL);
        }
        else if(elapsed_time_ms >= door.timeout) {
            door.state = Closed;
            break;
        }
        else {
            door.elapsed_time = time(NULL);
        }
        break;


    case Closed:
        elevio_doorOpenLamp(0);
        break;


    default:
        break;
    }
}

