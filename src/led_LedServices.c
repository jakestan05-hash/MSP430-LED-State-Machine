#include "common.h"
#include "led_LedServices.h"

//===========================================================================
// LED array
//===========================================================================
led_t led_Index[NUM_LEDS] = {
    {LED_1, BIT0, OFF},
    {LED_2, BIT1, OFF},
    {LED_3, BIT2, OFF},
    {LED_4, BIT3, OFF},
    {LED_5, BIT4, OFF}
};

//===========================================================================
// Initialize LEDs
//
// PxSEL0       controls port functionality
// PxSEL1       controls port functionality
// PxDIR        Sets port input or output
// PxOUT        Controls whether the output is high or low
//
// Sets each pin to a GPIO output that is currently off
//===========================================================================
void led_InitLeds(void){
    uint8 i;
    for(i = 0; i < NUM_LEDS; i++){

        P6SEL0 BCLR led_Index[i].pin;
        P6SEL1 BCLR led_Index[i].pin;
        P6DIR BSET led_Index[i].pin;
        P6OUT BCLR led_Index[i].pin;
    }
}

//===========================================================================
void led_Toggle(ledid_t led){
    if (led < LED_UPPERBOUND && led > LED_LOWERBOUND){
        P6OUT BTOG led_Index[led].pin;
    }
}

void led_TurnOff(ledid_t led){
    switch(led){
        case LED_ALL:
            ;
            uint8 i;
            for(i = 0; i< NUM_LEDS; i++){
                P6OUT BCLR led_Index[i].pin;
            }

            break;
        case LED_UPPERBOUND:

            break;
        case LED_LOWERBOUND:

            break;            
        default:
            if (led < LED_UPPERBOUND && led > LED_LOWERBOUND){
                P6OUT BCLR led_Index[led].pin;
            } 

            break;
    }
}
void led_TurnOn(ledid_t led){
    switch(led){
        case LED_ALL:
            ;
            uint8 i;
            for(i = 0; i< NUM_LEDS; i++){
                P6OUT BSET led_Index[i].pin;
            }

            break;
        case LED_UPPERBOUND:

            break;
        case LED_LOWERBOUND:

            break;
        default:
            if (led < LED_UPPERBOUND && led > LED_LOWERBOUND){
                P6OUT BSET led_Index[led].pin;
            } 

            break;
    }
}
