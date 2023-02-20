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
            return fromStill();
            break;
        case StillDown:
            return fromStill();
            break;
        case FloorHitUp:
            return fromFloorHit();
            break;
        case FloorhitDown:
            return fromFloorHit();
            break;
        default:
            printf("Unknown state has accured, please build a better elevator ...");
            break;
        }
    return next_state;
}

ElevatorState fromNeutral(){
    //1. Check order from whithin
    for(int f = 0; f < N_FLOORS; f++){ 
        if(order_list[f][2] == BTN_PRESSED && f > elevator.floor)
            return StillUp;
        else if(order_list[f][2] == BTN_PRESSED && f < elevator.floor)
            return StillDown;
        else if(order_list[f][2] == BTN_PRESSED && f == elevator.floor) // NB!!!
            return StillUp;
    }

    //2. Check for current floor
    if(order_list[elevator.floor][0])
        return StillUp;
    else if(order_list[elevator.floor][1])
        return StillDown;
    
    //2. Checks for orders from outside cabin
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < 2; b++){
            if(order_list[f][b] == BTN_PRESSED && f > elevator.floor)
                return StillUp;
            else if(order_list[f][b] == BTN_PRESSED && f < elevator.floor)
                return StillDown;
        }
    }
    
    //4. No orders found keeping neutral position
    return Neutral;
}

ElevatorState fromStill(){
    //Check for floor hit
    // if(order_list[elevator.floor][2] && elevator.state == StillUp)
    //     return FloorHitUp;
    // else if(order_list[elevator.floor][2] && elevator.state == StillDown)
    //     return FloorhitDown;

    //if no floor-hit, detmerine if we should keep going
    if(elevator.state == StillUp){
        for (int f = elevator.floor; f < 4; f++){
            if(order_list[f][0])
                return MovingUp;
            else if(f == 3 && order_list[f][1])
                return MovingUp;
        }
    }
    else if(elevator.state == StillDown){
        for (int f = elevator.floor; f >= 0; f--){
            if(order_list[f][1])
                return MovingDown;
            if(f == 0 && order_list[f][0])
                return MovingDown;
        }
    }

    //If there were no order from cabin, and no orders from outside:
    return Neutral;
}

ElevatorState fromFloorHit(){
    //Checks for request from within
    if(order_list[elevator.floor][2]){ //If someone also has requested from outside light impementation should update TWO lights
        if(elevator.state == FloorHitUp)
            return StillUp;
        else if(elevator.state == FloorhitDown)
            return StillDown;
    }

    //Checks for request from outside at current floor
    if(elevator.state == FloorHitUp){
        if(order_list[elevator.floor][0])
            return StillUp;
        //Checks for edge case
        else if(elevator.floor == 3){
            if(order_list[elevator.floor][1])
                return StillUp;
        }
    }
    else if(elevator.state == FloorhitDown){
        if(order_list[elevator.floor][1])
            return StillDown;
        //Checks for edge case
        else if(elevator.floor == 0){
            if(order_list[elevator.floor][0])
                return StillDown;
        }
    }
    
    //Check if we have reached one of the edges
    if(elevator.state == FloorHitUp && elevator.floor == 3)
        return StillUp;
    else if(elevator.state == FloorhitDown && elevator.floor == 0)
        return StillDown;
    
    //If no order from outside/innside and no edge case we should keep going
    if(elevator.state == FloorHitUp)
        return MovingUp;
    else if(elevator.state == FloorhitDown)
        return MovingDown;
    else{
        //This should never happen, but is implemented purly for debugging purposes
        printf("Error! Elevator is set to neutral position!\n");
        printf("Please build better elevator!\n");
        return Neutral;
    }
}
