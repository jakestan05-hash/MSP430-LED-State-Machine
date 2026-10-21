#include "common.h"

#define NUM_STATES 4

typedef enum {
    STATE_OFF,
    STATE_SPEED,
    STATE_DIRECTION,
    STATE_COUNTER
}state_t;

extern void sm_InitStateMachine(void);
extern state_t sm_GetState(void);
extern void sm_StateMachine(state_t state);

extern volatile state_t sm_CurrState;
extern volatile state_t sm_PrevState;
