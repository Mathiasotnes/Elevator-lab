

typedef enum Direction{
    up,
    down
} Direction;


struct Order{
    int start_floor;
    int stop_floor;
    Direction direction;
    int start_light;
    int stop_light;
};