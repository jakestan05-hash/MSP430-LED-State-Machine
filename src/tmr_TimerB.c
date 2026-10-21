#include "common.h"
#include "tmr_TimerB.h"

timerb_t *tmr_TimerBIndex[NUM_B_TIMERS];
volatile uint16 tmr_Ticks = 0;

//=========================================================================================
// INITIALIZE TIMER B MODULES
//
// This function initializes each TIMER B module and assigns it to its place in memory
// Each module is put into the TIMER B array
//=========================================================================================
void tmr_InitTimerPtrs(void){
    tmr_TimerBIndex[TIMERB0] = (timerb_t *) __MSP430_BASEADDRESS_TB0__; 
    tmr_TimerBIndex[TIMERB1] = (timerb_t *) __MSP430_BASEADDRESS_TB1__;
    tmr_TimerBIndex[TIMERB2] = (timerb_t *) __MSP430_BASEADDRESS_TB2__;
    tmr_TimerBIndex[TIMERB3] = (timerb_t *) __MSP430_BASEADDRESS_TB3__;
}

//=========================================================================================
// START TIMER B
//
// This function starts each individual timer
// parameters select which timer to start, which clock its using, and what mode it is in
//=========================================================================================
void tmr_StartTimer(uint16 timer, uint16 clock, uint16 mode){
    timerb_t *_timerptr;
    _timerptr = tmr_TimerBIndex[timer];

    _timerptr->TBxCTL BSET TBCLR;
    
    _timerptr->TBxEX0 = 0;
    _timerptr->TBxCCTL0 = 0;

    _timerptr->TBxCTL BSET clock;

    _timerptr->TBxCCTL0 BSET CAP__COMPARE;

    switch (clock){
        case TBSSEL__SMCLK:
            _timerptr->TBxCTL BSET ID__2;
            _timerptr->TBxEX0 BSET TBIDEX_0;
            _timerptr->TBxCCR0 = 4999;                       //~10ms ticks

            break;
        default:
            _timerptr->TBxCTL BSET ID__8;
            _timerptr->TBxEX0 BSET TBIDEX_7;
            _timerptr->TBxCCR0 = 4;                         //~10ms ticks

            break;
    }

    _timerptr->TBxCCTL0 BSET CCIE;
    _timerptr->TBxCCTL0 BCLR CCIFG;

    _timerptr->TBxCTL BSET mode;    

}


#pragma vector = TIMER0_B0_VECTOR
__interrupt void timer0_b0_isr(void){
    tmr_Ticks++;

    TB0CCTL0 BCLR CCIFG; //clear CCR0 flag
    TB0CTL BCLR TBIFG;   //clear interrupt flag
}
