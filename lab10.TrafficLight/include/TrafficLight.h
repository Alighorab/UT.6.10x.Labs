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
    EventType event;
    StateType next_state;
} TransMatrix;

typedef struct StateMachine {
    StateType state;
    void (*state_function)(unsigned long);
    unsigned long out;
    void (*wait)(unsigned long);
    unsigned long delay;
} StateMachine;

void system_init(void);
void system_out(unsigned long out);
void system_read_event(void);
void SysTick_init(void);
void SysTick_wait(unsigned long delay);
void SysTick_wait_10ms(unsigned long delay);

StateType state = ST_GO_SOUTH;
EventType event = EV_NO_MOVEMENT;

TransMatrix go_south_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_GO_SOUTH},
    {EV_CARS_EAST,       ST_WAIT_SOUTH},
    {EV_CARS_SOUTH,      ST_GO_SOUTH},
    {EV_BOTH_WAYS,       ST_WAIT_SOUTH},
    {EV_WALK_NO_CARS,    ST_WAIT_SOUTH},
    {EV_WALK_EAST,       ST_WAIT_SOUTH},
    {EV_WALK_SOUTH,      ST_WAIT_SOUTH},
    {EV_ALL,             ST_WAIT_SOUTH},
};

TransMatrix wait_south_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_GO_EAST},
    {EV_CARS_EAST,       ST_GO_EAST},
    {EV_CARS_SOUTH,      ST_GO_EAST},
    {EV_BOTH_WAYS,       ST_GO_EAST},
    {EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {EV_WALK_EAST,       ST_GO_EAST},
    {EV_WALK_SOUTH,      ST_WALK_GREEN},
    {EV_ALL,             ST_GO_EAST},
};

TransMatrix go_east_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_GO_EAST},
    {EV_CARS_EAST,       ST_GO_EAST},
    {EV_CARS_SOUTH,      ST_WAIT_EAST},
    {EV_BOTH_WAYS,       ST_WAIT_EAST},
    {EV_WALK_NO_CARS,    ST_WAIT_EAST},
    {EV_WALK_EAST,       ST_WAIT_EAST},
    {EV_WALK_SOUTH,      ST_WAIT_EAST},
    {EV_ALL,             ST_WAIT_EAST},

};

TransMatrix wait_east_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_GO_SOUTH},
    {EV_CARS_EAST,       ST_GO_SOUTH},
    {EV_CARS_SOUTH,      ST_GO_SOUTH},
    {EV_BOTH_WAYS,       ST_GO_SOUTH},
    {EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {EV_WALK_EAST,       ST_WALK_GREEN},
    {EV_WALK_SOUTH,      ST_GO_SOUTH},
    {EV_ALL,             ST_WALK_GREEN},

};

TransMatrix walk_green_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_WALK_GREEN},
    {EV_CARS_EAST,       ST_WALK_RED1},
    {EV_CARS_SOUTH,      ST_WALK_RED1},
    {EV_BOTH_WAYS,       ST_WALK_RED1},
    {EV_WALK_NO_CARS,    ST_WALK_GREEN},
    {EV_WALK_EAST,       ST_WALK_RED1},
    {EV_WALK_SOUTH,      ST_WALK_RED1},
    {EV_ALL,             ST_WALK_RED1},
};

TransMatrix walk_red1_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_WALK_OFF1},
    {EV_CARS_EAST,       ST_WALK_OFF1},
    {EV_CARS_SOUTH,      ST_WALK_OFF1},
    {EV_BOTH_WAYS,       ST_WALK_OFF1},
    {EV_WALK_NO_CARS,    ST_WALK_OFF1},
    {EV_WALK_EAST,       ST_WALK_OFF1},
    {EV_WALK_SOUTH,      ST_WALK_OFF1},
    {EV_ALL,             ST_WALK_OFF1},
};

TransMatrix walk_off1_trans_matrix[] = {
    {EV_NO_MOVEMENT,     ST_WALK_RED2},
    {EV_CARS_EAST,       ST_WALK_RED2},
    {EV_CARS_SOUTH,      ST_WALK_RED2},
    {EV_BOTH_WAYS,       ST_WALK_RED2},
    {EV_WALK_NO_CARS,    ST_WALK_RED2},
    {EV_WALK_EAST,       ST_WALK_RED2},
    {EV_WALK_SOUTH,      ST_WALK_RED2},
    {EV_ALL,             ST_WALK_RED2},
};

TransMatrix walk_red2_trans_matrix[] = {
    {EV_NO_MOVEMENT,      ST_WALK_OFF2},
    {EV_CARS_EAST,        ST_WALK_OFF2},
    {EV_CARS_SOUTH,       ST_WALK_OFF2},
    {EV_BOTH_WAYS,        ST_WALK_OFF2},
    {EV_WALK_NO_CARS,     ST_WALK_OFF2},
    {EV_WALK_EAST,        ST_WALK_OFF2},
    {EV_WALK_SOUTH,       ST_WALK_OFF2},
    {EV_ALL,              ST_WALK_OFF2},

};

TransMatrix walk_off2_trans_matrix[] = {
    {EV_NO_MOVEMENT,       ST_WALK_RED3},
    {EV_CARS_EAST,         ST_WALK_RED3},
    {EV_CARS_SOUTH,        ST_WALK_RED3},
    {EV_BOTH_WAYS,         ST_WALK_RED3},
    {EV_WALK_NO_CARS,      ST_WALK_RED3},
    {EV_WALK_EAST,         ST_WALK_RED3},
    {EV_WALK_SOUTH,        ST_WALK_RED3},
    {EV_ALL,               ST_WALK_RED3},
};

TransMatrix walk_red3_trans_matrix[] = {
    {EV_NO_MOVEMENT,        ST_WALK_OFF3},
    {EV_CARS_EAST,          ST_WALK_OFF3},
    {EV_CARS_SOUTH,         ST_WALK_OFF3},
    {EV_BOTH_WAYS,          ST_WALK_OFF3},
    {EV_WALK_NO_CARS,       ST_WALK_OFF3},
    {EV_WALK_EAST,          ST_WALK_OFF3},
    {EV_WALK_SOUTH,         ST_WALK_OFF3},
    {EV_ALL,                ST_WALK_OFF3},
};

TransMatrix walk_off3_trans_matrix[] = {
    {EV_NO_MOVEMENT,         ST_WALK_RED},
    {EV_CARS_EAST,           ST_WALK_RED},
    {EV_CARS_SOUTH,          ST_WALK_RED},
    {EV_BOTH_WAYS,           ST_WALK_RED},
    {EV_WALK_NO_CARS,        ST_WALK_RED},
    {EV_WALK_EAST,           ST_WALK_RED},
    {EV_WALK_SOUTH,          ST_WALK_RED},
    {EV_ALL,                 ST_WALK_RED},
};

TransMatrix walk_red_trans_matrix[] = {
    {EV_NO_MOVEMENT,         ST_GO_SOUTH},
    {EV_CARS_EAST,           ST_GO_EAST},
    {EV_CARS_SOUTH,          ST_GO_SOUTH},
    {EV_BOTH_WAYS,           ST_GO_SOUTH},
    {EV_WALK_NO_CARS,        ST_GO_SOUTH},
    {EV_WALK_EAST,           ST_GO_EAST},
    {EV_WALK_SOUTH,          ST_GO_SOUTH},
    {EV_ALL,                 ST_GO_SOUTH},
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
    {ST_GO_SOUTH,   system_out, GO_SOUTH,   SysTick_wait_10ms, LIGHTS_DELAY},
    {ST_WAIT_SOUTH, system_out, WAIT_SOUTH, SysTick_wait_10ms, LIGHTS_DELAY},
    {ST_GO_EAST,    system_out, GO_EAST,    SysTick_wait_10ms, LIGHTS_DELAY},
    {ST_WAIT_EAST,  system_out, WAIT_EAST,  SysTick_wait_10ms, LIGHTS_DELAY},
    {ST_WALK_GREEN, system_out, WALK_GREEN, SysTick_wait_10ms, LIGHTS_DELAY},
    {ST_WALK_RED1,  system_out, WALK_RED1,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_OFF1,  system_out, WALK_OFF1,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_RED2,  system_out, WALK_RED2,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_OFF2,  system_out, WALK_OFF2,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_RED3,  system_out, WALK_RED3,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_OFF3,  system_out, WALK_OFF3,  SysTick_wait_10ms, FLASHING_DELAY},
    {ST_WALK_RED,   system_out, WALK_RED,   SysTick_wait_10ms, LIGHTS_DELAY},
};
