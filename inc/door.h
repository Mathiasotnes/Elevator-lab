#ifndef INC_INTERFACE_H
#define INC_INTERFACE_H

#include <time.h>
#include "../driver/elevio.h"

typedef enum DoorState {
    Open,
    Closed
} DoorState;

typedef struct Door{
  DoorState state;
  int timeout;
  long start_time;  
  long elapsed_time;
} Door;

extern Door door;

/* Functions */
void initialize_door(int timeout);
void open_door();
void update_door();

#endif