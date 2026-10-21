#include "common.h"

#define NUM_LEDS 5
#define OFF 0
#define ON 1

typedef enum {
    LED_LOWERBOUND = -1,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_UPPERBOUND,
    LED_ALL 
}ledid_t;

//#define LED_LOWERBOUND -1
//#define LED_UPPERBOUND 5

typedef struct {
    uint8 id;
    uint8 pin;
    uint8 state;
} led_t;

extern led_t led_Index[NUM_LEDS];
extern void led_InitLeds(void);
extern void led_Toggle(ledid_t led);
extern void led_TurnOff(ledid_t led);
extern void led_TurnOn(ledid_t led);
