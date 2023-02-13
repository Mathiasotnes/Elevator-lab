#ifndef INC_INTERFACE_H
#define INC_INTERFACE_H

#include <time.h>
#include "../drivers/elevio.h"

typedef enum DoorState {
    Open,
    Closing,
    Closed
} DoorState;

typedef struct Door{
  DoorState state;
  int timeout;
  clock_t start_time;  
  clock_t elapsed_time;
} Door;

/* Functions */
Door* initialize_door(int timeout);

void update_door(Door *door);

#endif