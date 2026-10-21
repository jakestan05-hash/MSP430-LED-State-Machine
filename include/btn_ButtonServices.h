#include "common.h"

#define NUM_BUTTONS 3

enum buttonId_e {
    BUTTON_SWAPMODE,
    BUTTON_RIGHT,
    BUTTON_LEFT
};

typedef struct {
    uint8 id;
    uint8 pin;
    volatile uint8 flag;

    volatile uint8 *PxSEL0;
    volatile uint8 *PxSEL1;
    volatile uint8 *PxDIR;
    volatile uint8 *PxOUT;
    volatile uint8 *PxREN;

    volatile uint8 *PxIES;
    volatile uint8 *PxIFG;
    volatile uint8 *PxIE;
}button_t;

extern button_t btn_Index[NUM_BUTTONS];

extern void btn_InitButtons(void);
