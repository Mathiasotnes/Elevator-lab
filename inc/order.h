#ifndef INC_ORDER_H
#define INC_ORDER_H
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

#endif
