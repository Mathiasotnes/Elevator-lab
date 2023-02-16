#include "../inc/logic.h"
#include "../inc/elevator.h"
#include "../inc/order.h"
#include <stdio.h>

ElevatorState logic() {

    /* Dette er kun for å vise, current_floor og order_list bør bare */
    /* benyttes rett fra elevator objektet, mens next_state bør defineres som */
    /* en ny variabel siden den skal returneres */
    ElevatorState next_state = elevator.state;
    // int current_floor = elevator.floor;
    // Order order_list[20] = elevator.order_list;
    /*
        Implementer logikk basert på paramterere:
            - Tilstant til heis     elevator.state
            - Etasjen til heisen    elevator.floor
            - Ordreliste            elevator.order_list

        Logikken skal returnere hvilke state heisen skal inn i
        (next_state).    
    */

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

/**
 * TODO: What happens when order is coming ON current floor
 */
ElevatorState fromNeutral(){
    // 1. Check for edge-cases
    if(elevator.floor == 1 || elevator.floor == 4){
        for(int f = 0; f < N_FLOORS; f++){
            if(order_list[f][2] == BTN_PRESSED && f >= elevator.floor)
                return StillUp;
            else if(order_list[f][2] == BTN_PRESSED && f <= elevator.floor)
                return StillDown;   
        }
        
    /*
        for (int i = 0; i < 20; i++){
            if(elevator.order_list[i].valid){
                if(elevator.order_list[i].start_floor > elevator.floor)
                    return StillUp;
                else if(elevator.order_list[i].start_floor < elevator.floor)
                    return StillDown;
            }
        }
    */
    }

    //2. Check order from whithin
    for(int f = 0; f < N_FLOORS; f++){ 
        if(order_list[f][2] == BTN_PRESSED && f > elevator.floor)
            return StillUp;
        else if(order_list[f][2] == BTN_PRESSED && f < elevator.floor)
            return StillDown;
    }

    /*
    for (int i = 0; i < 20; i++){
        if(elevator.order_list[i].valid){
            if(elevator.order_list[i].stop_floor > elevator.floor)
                return StillUp;
            else if(elevator.order_list[i].stop_floor < elevator.floor)
                return StillDown;
        }
    }
    */
    
    //3. Checks for orders from outside cabin
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(order_list[f][b] == BTN_PRESSED && f > elevator.floor)
                return StillUp;
            else if(order_list[f][b] == BTN_PRESSED && f < elevator.floor)
                return StillDown;
        }
    }

    /*
    for (int i = 0; i < 20; i++){
        if(elevator.order_list[i].valid){
            if(elevator.order_list[i].start_floor > elevator.floor)
                return StillUp;
            else if(elevator.order_list[i].start_floor < elevator.floor)
                return StillDown;
        }
    }
    */
    
    //4. No orders found keeping neutral position
    return Neutral;
}

ElevatorState fromStill(){

    //Prioritze checking for floor hits with order list
    for(int f = 0; f < N_FLOORS; f++){
        if(order_list[f][2] == elevator.floor && elevator.state == StillUp)
            return FloorHitUp;
        else if(order_list[f][2] == elevator.floor && elevator.state == StillDown)
            return FloorhitDown;
    }

    /*
    for (int i = 0; i < 20; i++){
        if(elevator.order_list[i].valid){
            if (elevator.order_list[i].stop_floor == elevator.floor && elevator.state == StillUp)
                return FloorHitUp;
            else if (elevator.order_list[i].stop_floor == elevator.floor && elevator.state == StillDown)
                return FloorhitDown;
        }
    }
    */

    //if no floor-hit, detmerine if we should keep going
    for(int f = 0; f < N_FLOORS; f++){
        if(elevator.state == StillUp){
            if(order_list[f][0] && f > elevator.floor)
                return MovingUp;
        }
        if(elevator.state == StillDown){
            if(order_list[f][1] && f < elevator.floor)
                return MovingDown;
        }
    }

    /*
    for (int i = 0; i < 20; i++){
        if(elevator.order_list[i].valid){
            if(elevator.state == StillUp){
                if(elevator.order_list[i].direction == up && elevator.order_list[i].start_floor > elevator.floor)
                    return MovingUp;
            }
            if (elevator.state == StillDown){
                 if(elevator.order_list[i].direction == down && elevator.order_list[i].start_floor < elevator.floor)
                    return MovingDown;
            }
        }
    }
    */

    //If there were no order from cabin, and no orders from outside.
    //Elevator should be finished and go to neutral
    return Neutral;
}

ElevatorState fromFloorHit(){
    //Checks for edge cases
    //TODO: needs to be adressed in statediagram
    if(elevator.floor == 4)
        return Neutral;
    else if (elevator.floor == 1)
        return Neutral;

    //Checks if we should stop here
    //Important that order is deleted whithin next iteration else we are trapped
    for(int f = 0; f < N_FLOORS; f++){
        if(order_list[f][2] == BTN_PRESSED && f == elevator.floor){
            if(elevator.state == FloorHitUp)
                return StillUp;
            else if(elevator.state == FloorhitDown)
                return StillDown;
        }
    }

    /*
    for (int i = 0; i < 20; i++){
        if(elevator.order_list[i].valid){
            if(elevator.order_list[i].stop_floor == elevator.floor){
                if(elevator.state == FloorHitUp)
                    return StillUp;
                else if(elevator.state == FloorhitDown)
                    return StillDown;
            }
        }
    }
    */
    
    //If elevator is not stopping (if we are going XX we should keep going same direction)
    if(elevator.state == FloorHitUp)
        return MovingUp;
    else if(elevator.state == FloorhitDown)
        return MovingDown;
    else{
        //This should never happen, but is implemented purly for debugging purposes
        //printf("Elevator has come to undefined state based on current state: %s \n", to_state_str[elevator.state]);
        printf("Error! Elevator is set to neutral position!\n");
        printf("Please build beter elevator!\n");
        return Neutral;
    }
}
