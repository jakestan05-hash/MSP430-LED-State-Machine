//========================================================================================================
// LED CONTROL SYSTEM
// by Jake Stanley
//
// 4-28-2026
// Campbell University
// ELEC 325 Embedded Systems
// Copyright (c) 2026 Stanley
//========================================================================================================

#include "common.h"
#include "led_LedServices.h"
#include "btn_ButtonServices.h"
#include "tmr_TimerB.h"
#include "sm_StateMachine.h"

//===========================================================================
// Global variables
//===========================================================================
state_t sm_State;                                                               //State being used for control logic

//===========================================================================
// General Initialization
//===========================================================================
void InitGeneral(void){
    WDTCTL = WDTPW | WDTHOLD;                                                   //Stop the watchdog timer
    PM5CTL0 BCLR LOCKLPM5;                                                      //Turn on low power mode

    led_InitLeds();                                         
    btn_InitButtons();
    tmr_InitTimerPtrs();
    sm_InitStateMachine();
    tmr_StartTimer(TIMERB0, TBSSEL__SMCLK, MC__UP);
    __enable_interrupt();
}

//===========================================================================
// Scheduler
//
// Includes mainn state machine logic and reacts to state changes
//===========================================================================
void scheduler(){
    while(1){
        sm_State = sm_GetState();
        btn_Index[BUTTON_SWAPMODE].flag = false;                                //Acknowledge that state change request has been fulfilled
        while(btn_Index[BUTTON_SWAPMODE].flag == false){
            sm_StateMachine(sm_State);
        }
    }
}

//===========================================================================
// main
//===========================================================================
void main(void){
    InitGeneral();
    scheduler();
}
