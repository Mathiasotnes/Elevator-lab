#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "../driver/elevio.h"

#define BTN_PRESSED 1
#define BTN_NOT_PRESSED 0

extern int order_list[N_FLOORS][N_BUTTONS];

typedef enum Direction{
    up,
    down
} Direction;

/* returning array is not allowed, this is therefore */
/* a pointer to a matrix, be aware! OrderMatrix is a */
/* pointer to 4 pointers of 3 pointers to integers */

void initialize_order_list();
void create_order(int floor, ButtonType button_type);
void complete_order(int floor, ButtonType button_type);
void update_orders();
void clean_orders();

#endif
