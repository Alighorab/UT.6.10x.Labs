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

#define LIGHTS_DELAY    50
#define FLASHING_DELAY  25

typedef enum StateType {
    ST_GO_SOUTH = 0,
    ST_WAIT_SOUTH,
    ST_GO_EAST,
    ST_WAIT_EAST,
    ST_WALK_GREEN,
    ST_WALK_RED1,
    ST_WALK_OFF1,
    ST_WALK_RED2,
    ST_WALK_OFF2,
    ST_WALK_RED3,
    ST_WALK_OFF3,
    ST_WALK_RED
} StateType;

typedef enum EventType {
    EV_NO_MOVEMENT  = 0,
    EV_CARS_EAST,
    EV_CARS_SOUTH,
    EV_BOTH_WAYS,
    EV_WALK_NO_CARS,
    EV_WALK_EAST,
    EV_WALK_SOUTH,
    EV_ALL
} EventType;

typedef struct TransMatrix {
    StateType current_state;
    EventType event;
    StateType next_state;
} TransMatrix;

typedef struct StateMachine {
    StateType state;
    void (*state_function)(void);
    unsigned long delay;
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

TransMatrix go_south_trans_matrix[] = {
    {ST_GO_SOUTH,       EV_NO_MOVEMENT,     ST_GO_SOUTH},
    {ST_GO_SOUTH,       EV_CARS_EAST,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_CARS_SOUTH,      ST_GO_SOUTH},
    {ST_GO_SOUTH,       EV_BOTH_WAYS,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_NO_CARS,    ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_EAST,       ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_WALK_SOUTH,      ST_WAIT_SOUTH},
    {ST_GO_SOUTH,       EV_ALL,             ST_WAIT_SOUTH},
};

TransMatrix wait_south_trans_matrix[] = {
    {ST_WAIT_SOUTH,     EV_NO_MOVEMENT,     ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_CARS_EAST,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_CARS_SOUTH,      ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_BOTH_WAYS,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {ST_WAIT_SOUTH,     EV_WALK_EAST,       ST_GO_EAST},
    {ST_WAIT_SOUTH,     EV_WALK_SOUTH,      ST_WALK_GREEN},
    {ST_WAIT_SOUTH,     EV_ALL,             ST_GO_EAST},
};

TransMatrix go_east_trans_matrix[] = {
    {ST_GO_EAST,        EV_NO_MOVEMENT,     ST_GO_EAST},
    {ST_GO_EAST,        EV_CARS_EAST,       ST_GO_EAST},
    {ST_GO_EAST,        EV_CARS_SOUTH,      ST_WAIT_EAST},
    {ST_GO_EAST,        EV_BOTH_WAYS,       ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_NO_CARS,    ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_EAST,       ST_WAIT_EAST},
    {ST_GO_EAST,        EV_WALK_SOUTH,      ST_WAIT_EAST},
    {ST_GO_EAST,        EV_ALL,             ST_WAIT_EAST},

};

TransMatrix wait_east_trans_matrix[] = {
    {ST_WAIT_EAST,      EV_NO_MOVEMENT,     ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_CARS_EAST,       ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_CARS_SOUTH,      ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_BOTH_WAYS,       ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {ST_WAIT_EAST,      EV_WALK_EAST,       ST_WALK_GREEN},
    {ST_WAIT_EAST,      EV_WALK_SOUTH,      ST_GO_SOUTH},
    {ST_WAIT_EAST,      EV_ALL,             ST_WALK_GREEN},

};

TransMatrix walk_green_trans_matrix[] = {
    {ST_WALK_GREEN,     EV_NO_MOVEMENT,     ST_WALK_GREEN},
    {ST_WALK_GREEN,     EV_CARS_EAST,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_CARS_SOUTH,      ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_BOTH_WAYS,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {ST_WALK_GREEN,     EV_WALK_EAST,       ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_WALK_SOUTH,      ST_WALK_RED1},
    {ST_WALK_GREEN,     EV_ALL,             ST_WALK_RED1},
};

TransMatrix walk_red1_trans_matrix[] = {
    {ST_WALK_RED1,      EV_NO_MOVEMENT,     ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_CARS_EAST,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_CARS_SOUTH,      ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_BOTH_WAYS,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_NO_CARS,    ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_EAST,       ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_WALK_SOUTH,      ST_WALK_OFF1},
    {ST_WALK_RED1,      EV_ALL,             ST_WALK_OFF1},
};

TransMatrix walk_off1_trans_matrix[] = {
    {ST_WALK_OFF1,      EV_NO_MOVEMENT,     ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_CARS_EAST,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_CARS_SOUTH,      ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_BOTH_WAYS,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_NO_CARS,    ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_EAST,       ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_WALK_SOUTH,      ST_WALK_RED2},
    {ST_WALK_OFF1,      EV_ALL,             ST_WALK_RED2},
};

TransMatrix walk_red2_trans_matrix[] = {
    {ST_WALK_RED2,      EV_NO_MOVEMENT,      ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_CARS_EAST,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_CARS_SOUTH,       ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_BOTH_WAYS,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_NO_CARS,     ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_EAST,        ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_WALK_SOUTH,       ST_WALK_OFF2},
    {ST_WALK_RED2,      EV_ALL,              ST_WALK_OFF2},

};

TransMatrix walk_off2_trans_matrix[] = {
    {ST_WALK_OFF2,      EV_NO_MOVEMENT,       ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_CARS_EAST,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_CARS_SOUTH,        ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_BOTH_WAYS,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_NO_CARS,      ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_EAST,         ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_WALK_SOUTH,        ST_WALK_RED3},
    {ST_WALK_OFF2,      EV_ALL,               ST_WALK_RED3},
};

TransMatrix walk_red3_trans_matrix[] = {
    {ST_WALK_RED3,      EV_NO_MOVEMENT,        ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_CARS_EAST,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_CARS_SOUTH,         ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_BOTH_WAYS,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_NO_CARS,       ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_EAST,          ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_WALK_SOUTH,         ST_WALK_OFF3},
    {ST_WALK_RED3,      EV_ALL,                ST_WALK_OFF3},
};

TransMatrix walk_off3_trans_matrix[] = {
    {ST_WALK_OFF3,      EV_NO_MOVEMENT,         ST_WALK_RED},
    {ST_WALK_OFF3,      EV_CARS_EAST,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_CARS_SOUTH,          ST_WALK_RED},
    {ST_WALK_OFF3,      EV_BOTH_WAYS,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_NO_CARS,        ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_EAST,           ST_WALK_RED},
    {ST_WALK_OFF3,      EV_WALK_SOUTH,          ST_WALK_RED},
    {ST_WALK_OFF3,      EV_ALL,                 ST_WALK_RED},
};

TransMatrix walk_red_trans_matrix[] = {
    {ST_WALK_RED,       EV_NO_MOVEMENT,         ST_GO_SOUTH},
    {ST_WALK_RED,       EV_CARS_EAST,           ST_GO_EAST},
    {ST_WALK_RED,       EV_CARS_SOUTH,          ST_GO_SOUTH},
    {ST_WALK_RED,       EV_BOTH_WAYS,           ST_GO_SOUTH},
    {ST_WALK_RED,       EV_WALK_NO_CARS,        ST_GO_SOUTH},
    {ST_WALK_RED,       EV_WALK_EAST,           ST_GO_EAST},
    {ST_WALK_RED,       EV_WALK_SOUTH,          ST_GO_SOUTH},
    {ST_WALK_RED,       EV_ALL,                 ST_GO_SOUTH},
};

TransMatrix *trans_matrix[] = {
    go_south_trans_matrix,
    wait_south_trans_matrix,
    go_east_trans_matrix,
    wait_east_trans_matrix,
    walk_green_trans_matrix,
    walk_red1_trans_matrix,
    walk_off1_trans_matrix,
    walk_red2_trans_matrix,
    walk_off2_trans_matrix,
    walk_red3_trans_matrix,
    walk_off3_trans_matrix,
    walk_red_trans_matrix
};
StateMachine traffic_light[] = {
    {ST_GO_SOUTH,       system_go_south,        LIGHTS_DELAY},
    {ST_WAIT_SOUTH,     system_wait_south,      LIGHTS_DELAY},
    {ST_GO_EAST,        system_go_east,         LIGHTS_DELAY},
    {ST_WAIT_EAST,      system_wait_east,       LIGHTS_DELAY},
    {ST_WALK_GREEN,     system_walk_green,      LIGHTS_DELAY},
    {ST_WALK_RED1,      system_walk_red1,       FLASHING_DELAY},
    {ST_WALK_OFF1,      system_walk_off1,       FLASHING_DELAY},
    {ST_WALK_RED2,      system_walk_red2,       FLASHING_DELAY},
    {ST_WALK_OFF2,      system_walk_off2,       FLASHING_DELAY},
    {ST_WALK_RED3,      system_walk_red3,       FLASHING_DELAY},
    {ST_WALK_OFF3,      system_walk_off3,       FLASHING_DELAY},
    {ST_WALK_RED,       system_walk_red,        LIGHTS_DELAY},
};
