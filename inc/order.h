#ifndef INC_ORDER_H
#define INC_ORDER_H

#include "../drivers/elevio.h"

#define BTN_PRESSED 1
#define BTN_NOT_PRESSED 0

typedef enum Direction{
    up,
    down
} Direction;


typedef struct Order{
    int valid; //Denne er midlertidig intil bedre løsning
    int start_floor;
    int stop_floor;
    Direction direction;
    int start_light;
    int stop_light;
    short int order_ID;
}Order;

typedef int OrderMatrix[N_FLOORS][N_BUTTONS];

/* returning array is not allowed, this is therefore */
/* a pointer to a matrix, be aware! OrderMatrix is a */
/* pointer to 4 pointers of 3 pointers to integers */

OrderMatrix* initialize_order_list();
void create_order(OrderMatrix* order_list, int floor, ButtonType button_type);
void complete_order(OrderMatrix* order_list, int floor, ButtonType button_type);
void update_orders(OrderMatrix* order_list);

#endif
