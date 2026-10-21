//=======================================================================================================
// CODING STANDARD 
//
// •	constants in caps                                           CONSTANT
// •	No magic numbers, must use constants or enums               #define CONSTANT 1
// •	Global variables have meaningful prefix and camel case      tmr_GlobalVariable
// •	Function names use camel case verb + noun                   set_FunctionName(void) 
// •	File name use prefix that matches with vars                 led_LedServices.c
// •	Local variables underscore and lowercase                    _local                          
// •	Parameter all lowercase                                     set_FunctionName(uint8 par)
// •	For loops use I,j,k                                         for (uint16 i = 0, i < n, i++)
// •	Return value “_retval” w/initialization                     return _retval
// •	flags with prefix flg_                                      flg_FLAG
// •	Counts with prefix cnt_                                     cnt_counter
// •	while loops                                                 while (flg_FLAG == true)
// •	Index – into array “par”
//========================================================================================================

#ifndef COMMON_H
#define COMMON_H

#include <msp430.h>


typedef unsigned char uint8;
typedef unsigned int uint16;


//===========================================================================
// BITWISE FUNCTIONS
//===========================================================================
#define BCLR &= ~
#define BSET |= 
#define BTOG ^=

//===========================================================================
// LOGIC
//===========================================================================
#define false 0
#define true 1

#define RESET 0

#endif
