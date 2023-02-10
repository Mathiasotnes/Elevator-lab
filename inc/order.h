
typedef enum Direction{
    up,
    down
} Direction;


/* Ikke helt fornøyd med denne, bør revideres før logikk-implementasjon */
typedef struct Order{
    int start_floor;
    int stop_floor;
    Direction direction;
    int start_light;
    int stop_light;
    short int order_ID;
} Order;

