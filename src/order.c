#include "../drivers/elevio.h"
#include "../inc/order.h"


OrderMatrix* initialize_order_list() {
    OrderMatrix* order_list;
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                    complete_order(order_list, f, b);
                }
            }
    return order_list;
}

/* floor is zero-indexed, should be called from update_orders which */
/* works with the zero-indexed floor variable "f" */
void create_order(OrderMatrix* order_list, int floor, ButtonType button_type) {
    *order_list[floor][button_type] = BTN_PRESSED;
    elevio_buttonLamp(floor, button_type, BTN_PRESSED);
}

void complete_order(OrderMatrix* order_list, int floor, ButtonType button_type) {
    *order_list[floor][button_type] = BTN_NOT_PRESSED;
    elevio_buttonLamp(floor, button_type, BTN_NOT_PRESSED);
}

void update_orders(OrderMatrix* order_list) {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed && *order_list[f][b] == BTN_NOT_PRESSED) {
                    create_order(order_list, f, b);
                }
            }
    }
}



