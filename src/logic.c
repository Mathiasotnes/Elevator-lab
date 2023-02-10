#include "../inc/logic.h"

ElevatorState logic(Elevator* elevator) {

    /* Dette er kun for å vise, current_floor og order_list bør bare */
    /* benyttes rett fra elevator objektet, mens next_state bør defineres som */
    /* en ny variabel siden den skal returneres */
    ElevatorState next_state = elevator->state;
    // int current_floor = elevator->floor;
    // Order order_list[20] = elevator->order_list;
    /*
        Implementer logikk basert på paramterere:
            - Tilstant til heis     elevator->state
            - Etasjen til heisen    elevator->floor
            - Ordreliste            elevator->order_list

        Logikken skal returnere hvilke state heisen skal inn i
        (next_state).    
    */

        switch (elevator->state)
        {
        case Neutral:
            // Christoffers Algoritme 1 :)
            break;
        case StillUp:
            // Christoffers Algoritme 2 :)
            break;
        case StillDown:
            // Christoffers Algoritme 2 :)
            break;
        case FloorHitUp:
            // Christoffers Algoritme 3 :)
            break;
        case FloorhitDown:
            // Christoffers Algoritme 3 :)
            break;
        default:
            break;
        }
    return next_state;
}

