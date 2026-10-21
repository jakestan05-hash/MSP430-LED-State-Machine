#ifndef TIMERB_H
#define TIMERB_H

#include "common.h"

typedef struct {
  
  unsigned int TBxCTL;      //00 Timer_B Control 
  unsigned int TBxCCTL0;    //02 Timer_B Capture/Compare Control 0
  unsigned int TBxCCTL1;    //04 Timer_B Capture/Compare Control 1
  unsigned int TBxCCTL2;    //06 Timer_B Capture/Compare Control 2
  unsigned int TBxCCTL3;    //08 Timer_B Capture/Compare Control 3
  unsigned int TBxCCTL4;    //0A Timer_B Capture/Compare Control 4
  unsigned int TBxCCTL5;    //0C Timer_B Capture/Compare Control 5
  unsigned int TBxCCTL6;    //0E Timer_B Capture/Compare Control 6
  
  unsigned int TBxR;        //10 Timer_B Counter
  
  unsigned int TBxCCR0;     //12 Timer_B Capture/Compare 0
  unsigned int TBxCCR1;     //14 Timer_B Capture/Compare 1
  unsigned int TBxCCR2;     //16 Timer_B Capture/Compare 2
  unsigned int TBxCCR3;     //18 Timer_B Capture/Compare 3
  unsigned int TBxCCR4;     //1A Timer_B Capture/Compare 4
  unsigned int TBxCCR5;     //1C Timer_B Capture/Compare 5
  unsigned int TBxCCR6;     //1E Timer_B Capture/Compare 6
  
  unsigned int TBxEX0;      //20 Timer_B Expansion 0
   
  int RESERVED0[6];         //22-2C RESERVED
  
  unsigned int TBxIV;       //2E Timer_B Interrupt Vector
  
}timerb_t;

enum timerB {
    TIMERB0,
    TIMERB1,
    TIMERB2,
    TIMERB3
};

#define NUM_B_TIMERS 4

#define SPEED_50MS 5
#define SPEED_100MS 10
#define SPEED_500MS 50
#define SPEED_1000MS 100
#define SPEED_INC 5

extern timerb_t *tmr_TimerBIndex[NUM_B_TIMERS];
extern volatile uint16 tmr_Ticks;

extern void tmr_InitTimerPtrs(void);
extern void tmr_StartTimer(uint16 timer, uint16 clock, uint16 mode);

#endif
