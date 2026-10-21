//===========================================================================
// INCLUDES
//===========================================================================
#include "common.h"
#include "sm_StateMachine.h"
#include "tmr_TimerB.h"
#include "led_LedServices.h"
#include "btn_ButtonServices.h"

//===========================================================================
// VARAIBLES
//===========================================================================
volatile state_t sm_CurrState;                                                  //Current State
volatile state_t sm_PrevState;                                                  //Used to keep track of when a state is on its first loop
volatile uint16 sm_BlinkSpeed;                                                  //Speed that LEDs update
ledid_t _led;                                                                   //LED being used for animation or simple LED control

// ** Counter State Only **
ledid_t _curr;                                                                      //Current counter value 
ledid_t _target;                                                                    //Counter value being moved to
uint8 flag_loopStart;                                                           //Used to flag when a +/- button has just been pressed and set intitial conditions

//===========================================================================
// Initialize State Machine
//
// sets initial state to off
//===========================================================================
void sm_InitStateMachine(void){
    sm_CurrState = STATE_OFF;
}

//===========================================================================
// Get State
//
// Gets the current state to pass to the State Machine Function
//===========================================================================
state_t sm_GetState(void){
    state_t _retval = sm_CurrState;
    return _retval;
}

//===========================================================================
// State Machine 
//
// contains control logic for each state
//===========================================================================
void sm_StateMachine(state_t state){
    switch(state){

//===========================================================================
// OFF 
//
// LEDs remain off, Buttons have no function
//===========================================================================
        case STATE_OFF: 
            if (state != sm_PrevState){
                led_TurnOff(LED_ALL);
                sm_BlinkSpeed = SPEED_1000MS;
            } 

            if (tmr_Ticks >= sm_BlinkSpeed) {
                tmr_Ticks = RESET;
            }
        
            break;

//===========================================================================
// SPEED CHANGE 
//
// LEDs sweep across, speed is changed by button presses
//
// RIGHT BUTTON -> Faster
// LEFT BUTTON -> Slower
//===========================================================================
        case STATE_SPEED:
            if (state != sm_PrevState){
                tmr_Ticks = RESET;
                sm_BlinkSpeed = SPEED_500MS;
                _led = LED_1;
                led_TurnOff(LED_ALL);
            }

            if(tmr_Ticks >= sm_BlinkSpeed){ 
                led_Toggle(_led);
                _led++;

                if(_led >= NUM_LEDS){
                    _led = LED_1;
                }
                tmr_Ticks = RESET;
            }

            if (btn_Index[BUTTON_RIGHT].flag == true){
                 btn_Index[BUTTON_RIGHT].flag = false;

                if (sm_BlinkSpeed > SPEED_50MS){
                    sm_BlinkSpeed -= SPEED_INC;
                } else {
                    sm_BlinkSpeed = SPEED_50MS;
                }
                
            } else if (btn_Index[BUTTON_LEFT].flag == true){
                btn_Index[BUTTON_LEFT].flag = false;
                
                if (sm_BlinkSpeed < SPEED_1000MS){
                    sm_BlinkSpeed += SPEED_INC;
                } else {
                    sm_BlinkSpeed = SPEED_1000MS;
                }
            }
            break;

//===========================================================================
// DIRECTION CHANGE 
//
// LEDs sweep back and forth when prompted by button presses
//
// RIGHT BUTTON -> sweep right
// LEFT BUTTON -> sweep left
//===========================================================================
        case STATE_DIRECTION:
            if (state != sm_PrevState){
                tmr_Ticks = RESET;
                sm_BlinkSpeed = SPEED_100MS;
                _led = LED_1;
                led_TurnOff(LED_ALL);
                led_TurnOn(_led);
            }

            if (btn_Index[BUTTON_LEFT].flag == true){
                if(tmr_Ticks >= sm_BlinkSpeed){
                    if (_led < LED_5) {
                        led_TurnOff(_led);
                        _led++;
                        led_TurnOn(_led);
                    } else {
                        btn_Index[BUTTON_LEFT].flag = false;
                    }

                    tmr_Ticks = RESET;
                }
            } else if (btn_Index[BUTTON_RIGHT].flag == true){
                if(tmr_Ticks >= sm_BlinkSpeed){
                    if (_led > LED_1) {
                        led_TurnOff(_led);
                        _led--;
                        led_TurnOn(_led);
                    } else {
                        btn_Index[BUTTON_RIGHT].flag = false;
                    }
                    tmr_Ticks = RESET;
                }

            }

            break;

//===========================================================================
// COUNTER STATE
//
// LEDs can be added or subtracted by button presses
//
// RIGHT BUTTON -> add
// LEFT BUTTON -> subtract
//===========================================================================
        case STATE_COUNTER:
             if (state != sm_PrevState){
                tmr_Ticks = RESET;
                led_TurnOff(LED_ALL);
                flag_loopStart = true;
                sm_BlinkSpeed = SPEED_50MS;
                _curr = LED_5;
                _target = _curr;
                led_TurnOn(LED_5);
            }

            if (btn_Index[BUTTON_RIGHT].flag == true){ //add
                if (tmr_Ticks >= sm_BlinkSpeed){

                    if (flag_loopStart == true){
                        if (_curr > LED_1) {
                            _target--;
                        }  
                        _led = LED_1;
                        flag_loopStart = false;
                    }

                    if (_curr > LED_LOWERBOUND) {
                        led_TurnOn(_led);
                        if (_led != LED_1) {
                            _led--;
                            led_TurnOff(_led);
                            _led++;
                        }
                        _led++;

                        if (_led >= _target) {
                            _led = _target;
                            led_TurnOn(_led);
                            _led--;
                            led_TurnOff(_led);
                            _curr = _target;
                            flag_loopStart = true;
                            btn_Index[BUTTON_RIGHT].flag = false;
                        }
                    } else if (_curr <= LED_LOWERBOUND) {
                        _curr = LED_LOWERBOUND;
                        _target = _curr;
                        flag_loopStart = true;
                        btn_Index[BUTTON_RIGHT].flag = false;
                    }

                    tmr_Ticks = RESET;
                }

            }
            if (btn_Index[BUTTON_LEFT].flag == true){ //sub
                if (tmr_Ticks >= sm_BlinkSpeed){

                    if (flag_loopStart == true){
                        _target++;
                        _led = _curr;
                        flag_loopStart = false;
                    }

                    if (_curr < LED_UPPERBOUND) {
                        led_TurnOff(_led);
                        if (_led != LED_1){
                            _led--;
                            led_TurnOn(_led);
                            _led++;
                        }
                        _led--;

                        if (_led == LED_LOWERBOUND) {
                            _curr = _target;
                            flag_loopStart = true;
                            btn_Index[BUTTON_LEFT].flag = false;
                        }

                    } else if (_curr >= LED_UPPERBOUND) {
                        _curr = LED_UPPERBOUND;
                        _target = _curr;
                        flag_loopStart = true;
                        btn_Index[BUTTON_LEFT].flag = false;
                    }                 
                    
                    tmr_Ticks = RESET;
                }
            }

            break;
    }
    sm_PrevState = state;
}
