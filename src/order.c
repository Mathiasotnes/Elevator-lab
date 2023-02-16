#include "../driver/elevio.h"
#include "../inc/order.h"


void initialize_order_list() {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                    complete_order(f, b);
                }
            }
}

/* floor is zero-indexed, should be called from update_orders which */
/* works with the zero-indexed floor variable "f" */
void create_order(int floor, ButtonType button_type) {
    order_list[floor][button_type] = BTN_PRESSED;
    elevio_buttonLamp(floor, button_type, BTN_PRESSED);
}

void complete_order(int floor, ButtonType button_type) {
    order_list[floor][button_type] = BTN_NOT_PRESSED;
    elevio_buttonLamp(floor, button_type, BTN_NOT_PRESSED);
}

void update_orders() {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed && order_list[f][b] == BTN_NOT_PRESSED) {
                    create_order(f, b);
                }
            }
    }
}



