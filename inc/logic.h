#ifndef INC_LOGIC_H
#define INC_LOGIC_H
#include "../inc/elevator.h"

/**
 * @brief This determines the next state based on current state and order
 * 
 * @param elevator 
 * @return ElevatorState 
 */
ElevatorState logic(Elevator* elevator);

/**
 * @brief Determines if we should go up or down, based on neutral state.
 * This means that it will first check for order coming from within the cabin
 * Before checking for order from outside (up/down)
 * 
 * @param elevator 
 * @return ElevatorState 
 */
ElevatorState fromNeutral(Elevator *elevator);

/**
 * @brief 
 * 
 * @param elevator 
 * @return ElevatorState 
 */
ElevatorState fromStill(Elevator *elevator);

/**
 * @brief Gets called from fsm, when floor hit has accured.
 *  Then detemrine the direction we should keep going in
 * 
 * @param elevator 
 * @return ElevatorState 
 */
ElevatorState fromFloorHit(Elevator *elevator);

#endif