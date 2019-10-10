/*----------------------------------------------------------------------------
 Switches C file
 *----------------------------------------------------------------------------*/
#include "switches.h"

void init_switches(void){
	//Start clocks for ports A and B
	RCC->AHB1ENR |= RCC_PORTA_MASK | RCC_PORTB_MASK;

	//Set pins to input mode:
	GPIOA->MODER &= ~MODER(SWITCH_1);
	//Write your code here
	GPIOB->MODER &= (~MODER(SWITCH_2) & ~MODER(SWITCH_3) & ~MODER(SWITCH_4));
	

	//Set pins to pull-up mode
	GPIOA->PUPDR |= PUPDR_0(SWITCH_1);
	GPIOB->PUPDR |= PUPDR_0(SWITCH_2) | PUPDR_0(SWITCH_3) | PUPDR_0(SWITCH_4);
}
// Understanding stm32 arm controller gpio

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
