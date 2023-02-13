#include "../drivers/elevio.h"
#include "../inc/order.h"


void update_orders(Order* order_list) {
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
    }
}

void complete_order(Order* order) {
    // fckin obliterate the order
}

