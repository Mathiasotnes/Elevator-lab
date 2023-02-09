
typedef enum Direction{
    up,
    down
};


typedef struct Order{
    int start_floor;
    int stop_floor;
    Direction direction;
    bool start_light;
    bool stop_light;
}