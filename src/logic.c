#include "../inc/logic.h"
#include "../inc/elevator.h"
#include "../inc/order.h"
#include <stdio.h>

ElevatorState logic() {

    ElevatorState next_state = elevator.state;

        switch (elevator.state)
        {
        case Neutral:
            return fromNeutral();
            break;
        case StillUp:
            return fromStillUp();
            break;
        case StillDown:
            return fromStillDown();
            break;
        case FloorHitUp:
            return fromFloorHitUp();
            break;
        case FloorhitDown:
            return fromFloorHitDown();
            break;
        default:
            printf("Unknown state has accured, please build a better elevator ...");
            break;
        }
    return next_state;
}

ElevatorState fromNeutral(){
    //Check current floor
    if(order_list[elevator.floor][0]) {
        return StillUp;
    }
    else if(order_list[elevator.floor][1]) {
        return StillDown;
    }
    //Check if orders downwards exists
    for(int f = elevator.floor; f >= 0; f--) {
        for(int b = 0; b <= 2; b++) {
            if(order_list[f][b]) {
                return StillDown;
            }
        }
    }
    //Check if orders upwards exists
    for(int f = elevator.floor; f < 4; f++) {
        for(int b = 0; b <= 2; b++) {
            if(order_list[f][b]) {
                return StillUp;
            }
        }
    }
    return Neutral;
}

ElevatorState fromStillUp(){
    //Check buttons in coupè
    for(int f = elevator.floor; f < 4; f++) {
        if(order_list[f][2]) {
            return MovingUp;
        }
    }
    //Check all the up-buttons above
    for(int f = elevator.floor; f < 4; f++) {
        if(order_list[f][0]) {
            return MovingUp;
        }
    }
    //Check all the down-buttons above
    for(int f = 3; f > elevator.floor; f--) {
        if(order_list[f][1]) {
            return MovingUp;
        }
    }
    //No orders below -> go to neutral.
    return Neutral;
}

ElevatorState fromStillDown() {
    //Check buttons in coupè
    for(int f = elevator.floor; f >= 0; f--) {
        if(order_list[f][2]) {
            return MovingDown;
        }
    }
    //Check all the down-buttons below
    for(int f = elevator.floor; f >= 0; f--) {
        if(order_list[f][1]) {
            return MovingDown;
        }
    }
    //Check all the up-buttons below
    for(int f = 0; f < elevator.floor; f++) {
        if(order_list[f][0]) {
            return MovingDown;
        }
    }
    //No orders below -> go to neutral.
    return Neutral;
}

ElevatorState fromFloorHitUp(){
    //Check for edge-cases
    if(elevator.floor == 3) {
        return Neutral;
    }
    return StillUp;
}

ElevatorState fromFloorHitDown() {
    //Check for edge-cases
    if(elevator.floor == 0) {
        return Neutral;
    }
    return StillDown;
}
