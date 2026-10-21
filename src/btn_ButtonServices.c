
//=====================================================================================
// INCLUDES
//=====================================================================================
#include "common.h"
#include "btn_ButtonServices.h"
#include "sm_StateMachine.h"

//=====================================================================================
// Button array
//=====================================================================================
button_t btn_Index[NUM_BUTTONS] = {
    {BUTTON_SWAPMODE, BIT1, false, &P1SEL0, &P1SEL1, &P1DIR, &P1OUT, &P1REN, &P1IES, &P1IFG, &P1IE},
    {BUTTON_RIGHT, BIT3, false, &P2SEL0, &P2SEL1, &P2DIR, &P2OUT, &P2REN, &P2IES, &P2IFG, &P2IE},
    {BUTTON_LEFT, BIT1, false, &P4SEL0, &P4SEL1, &P4DIR, &P4OUT, &P4REN, &P4IES, &P4IFG, &P4IE}
};

//=====================================================================================
// Initialize Buttons
//
// PxSEL0       controls port functionality
// PxSEL1       controls port functionality
// PxDIR        Sets port input or output
// PxREN        Enables use of pull up or pull down resistor
// PxOUT        Selects pull up or pulldown resistor
//
// PxIES        Selects the edge as low-to-high or high-to-low
// PxIFG        Flags that interrupt has occurred 
// PxIE         Enables port interrupts on selected pin
//
// Sets each pin to a GPIO input with a pull-up resistor and high-to-low edge
//=====================================================================================
void btn_InitButtons(void){
    uint8 i;
    uint8 _pin;
    for(i = 0; i < NUM_BUTTONS; i++){
        _pin = btn_Index[i].pin;

        *(btn_Index[i].PxSEL0) BCLR _pin;
        *(btn_Index[i].PxSEL1) BCLR _pin;
        *(btn_Index[i].PxDIR) BCLR _pin;
        *(btn_Index[i].PxOUT) BSET _pin;                                                //pull up resistor 
        *(btn_Index[i].PxREN) BSET _pin;

        *(btn_Index[i].PxIES) BSET _pin;                                                //high-to-low
        *(btn_Index[i].PxIFG) BCLR _pin;
        *(btn_Index[i].PxIE) BSET _pin;
    }
}

//=====================================================================================
// ISR for buttons
//=====================================================================================
#pragma vector = PORT1_VECTOR
__interrupt void ISR_SwapModeButton(void){

    btn_Index[BUTTON_SWAPMODE].flag = true;
    sm_CurrState++;
    if (sm_CurrState >= NUM_STATES){
        sm_CurrState = STATE_OFF;
    }
    P1IFG BCLR BIT1;                                                                    //clear 1.1 interrupt flag
}

#pragma vector = PORT2_VECTOR
__interrupt void ISR_RightButton(void){
    btn_Index[BUTTON_RIGHT].flag = true;

    P2IFG BCLR BIT3;                                                                    //clear 2.3 interrupt flag
}

#pragma vector = PORT4_VECTOR
__interrupt void ISR_LeftButton(void){
    btn_Index[BUTTON_LEFT].flag = true;


    P4IFG BCLR BIT1;                                                                     //clear 4.1 interrupt flag
}
