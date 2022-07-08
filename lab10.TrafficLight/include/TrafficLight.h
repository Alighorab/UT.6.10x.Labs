#define GO_SOUTH   0x85
#define WAIT_SOUTH 0x89
#define GO_EAST    0x31
#define WAIT_EAST  0x51
#define WALK_GREEN 0x92
#define WALK_RED1  0x91
#define WALK_OFF1  0x90
#define WALK_RED2  0x91
#define WALK_OFF2  0x90
#define WALK_RED3  0x91
#define WALK_OFF3  0x90
#define WALK_RED   0x91

typedef enum StateType {
    ST_GO_SOUTH   = 0,
    ST_WAIT_SOUTH = 1,
    ST_GO_EAST    = 2,
    ST_WAIT_EAST  = 3,
    ST_WALK_GREEN = 4,
    ST_WALK_RED1  = 5,
    ST_WALK_OFF1  = 6,
    ST_WALK_RED2  = 7,
    ST_WALK_OFF2  = 8,
    ST_WALK_RED3  = 9,
    ST_WALK_OFF3  = 10,
    ST_WALK_RED   = 11
} StateType;

typedef enum EventType {
    EV_NO_MOVEMENT  = 0b000,
    EV_CARS_EAST    = 0b001,
    EV_CARS_SOUTH   = 0b010,
    EV_BOTH_WAYS    = 0b011,
    EV_WALK_NO_CARS = 0b100,
    EV_WALK_EAST    = 0b101,
    EV_WALK_NORTH   = 0b110,
    EV_ALL          = 0b111
} EventType;

typedef struct TransMatrix {
    StateType current_state;
    EventType event;
    StateType next_state;
} TransMatrix;

typedef struct StateMachine {
    StateType state;
    void (*state_function)(void);
} StateMachine;

void system_init(void);
void system_go_south(void);
void system_wait_south(void);
void system_go_east(void);
void system_wait_east(void);
void system_walk_green(void);
void system_walk_red1(void);
void system_walk_off1(void);
void system_walk_red2(void);
void system_walk_off2(void);
void system_walk_red3(void);
void system_walk_off3(void);
void system_walk_red(void);
void system_read_event(void);

StateType state = ST_GO_SOUTH;
EventType event = EV_NO_MOVEMENT;
TransMatrix trans_matrix[] = {
    {ST_GO_SOUTH,       EV_CARS_EAST,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_BOTH_WAYS,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_NO_CARS,    ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_EAST,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_NORTH,      ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_ALL,             ST_WAIT_SOUTH},
    
    {ST_WAIT_SOUTH,     EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {ST_WAIT_SOUTH,     EV_WALK_NORTH,      ST_WALK_GREEN},
    {ST_WAIT_SOUTH,     EV_NO_MOVEMENT,     ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_CARS_EAST,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_CARS_SOUTH,      ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_BOTH_WAYS,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_WALK_EAST,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_ALL,             ST_GO_EAST},

    {ST_GO_EAST,        EV_CARS_SOUTH,      ST_WAIT_EAST},
    {ST_GO_EAST,        EV_BOTH_WAYS,       ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_NO_CARS,    ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_EAST,       ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_NORTH,      ST_WAIT_EAST},
    {ST_GO_EAST,        EV_ALL,             ST_WAIT_EAST},

    {ST_WAIT_EAST,      EV_NO_MOVEMENT,     ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_CARS_EAST,       ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_CARS_SOUTH,      ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_BOTH_WAYS,       ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {ST_WAIT_EAST,      EV_WALK_EAST,       ST_WALK_GREEN},
    {ST_WAIT_EAST,      EV_WALK_NORTH,      ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_ALL,             ST_WALK_GREEN},

    {ST_WALK_GREEN,     EV_CARS_EAST,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_CARS_SOUTH,      ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_BOTH_WAYS,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_WALK_EAST,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_WALK_NORTH,      ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_ALL,             ST_WALK_RED1},

    {ST_WALK_RED1,      EV_NO_MOVEMENT,     ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_CARS_EAST,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_CARS_SOUTH,      ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_BOTH_WAYS,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_NO_CARS,    ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_EAST,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_NORTH,      ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_ALL,             ST_WALK_OFF1},
    
    {ST_WALK_OFF1,      EV_NO_MOVEMENT,     ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_CARS_EAST,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_CARS_SOUTH,      ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_BOTH_WAYS,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_NO_CARS,    ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_EAST,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_NORTH,      ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_ALL,             ST_WALK_RED2},

    {ST_WALK_RED2,      EV_NO_MOVEMENT,      ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_CARS_EAST,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_CARS_SOUTH,       ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_BOTH_WAYS,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_NO_CARS,     ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_EAST,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_NORTH,       ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_ALL,              ST_WALK_OFF2},

    {ST_WALK_OFF2,      EV_NO_MOVEMENT,       ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_CARS_EAST,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_CARS_SOUTH,        ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_BOTH_WAYS,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_NO_CARS,      ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_EAST,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_NORTH,        ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_ALL,               ST_WALK_RED3},

    {ST_WALK_RED3,      EV_NO_MOVEMENT,        ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_CARS_EAST,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_CARS_SOUTH,         ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_BOTH_WAYS,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_NO_CARS,       ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_EAST,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_NORTH,         ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_ALL,                ST_WALK_OFF3},

    {ST_WALK_OFF3,      EV_NO_MOVEMENT,         ST_WALK_RED},
    {ST_WALK_OFF3,      EV_CARS_EAST,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_CARS_SOUTH,          ST_WALK_RED},
    {ST_WALK_OFF3,      EV_BOTH_WAYS,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_NO_CARS,        ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_EAST,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_NORTH,          ST_WALK_RED},
    {ST_WALK_OFF3,      EV_ALL,                 ST_WALK_RED},

    {ST_WALK_RED,       EV_NO_MOVEMENT,         ST_GO_SOUTH},
    {ST_WALK_RED,       EV_CARS_EAST,           ST_GO_EAST},
    {ST_WALK_RED,       EV_CARS_SOUTH,          ST_GO_SOUTH},
    {ST_WALK_RED,       EV_BOTH_WAYS,           ST_GO_SOUTH},
    {ST_WALK_RED,       EV_WALK_NO_CARS,        ST_GO_SOUTH},
    {ST_WALK_RED,       EV_WALK_EAST,           ST_GO_EAST},
    {ST_WALK_RED,       EV_WALK_NORTH,          ST_GO_SOUTH},
    {ST_WALK_RED,       EV_ALL,                 ST_GO_SOUTH},
};
StateMachine traffic_light[] = {
    {ST_GO_SOUTH,       system_go_south},
    {ST_WAIT_SOUTH,     system_wait_south},
    {ST_GO_EAST,        system_go_east},
    {ST_WAIT_EAST,      system_wait_east},
    {ST_WALK_GREEN,     system_walk_green},
    {ST_WALK_RED1,      system_walk_red1},
    {ST_WALK_OFF1,      system_walk_off1},
    {ST_WALK_RED2,      system_walk_red2},
    {ST_WALK_OFF2,      system_walk_off2},
    {ST_WALK_RED3,      system_walk_red3},
    {ST_WALK_OFF3,      system_walk_off3},
    {ST_WALK_RED,       system_walk_red}
};

const unsigned long TRANS_MATRIX_SIZE = 
                    sizeof(trans_matrix)/sizeof(TransMatrix);
