/*----------------------------------------------------------------------------
LAB EXERCISE - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.

	Inputs: potentiometers 1 and 2
	Output: speaker, PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"

/*
Define the PWM speaker output
Define analog inputs
*/
AnalogIn pot1(PA_0);
AnalogIn pot2(PA_1);
PwmOut out(PB_10);

//Define variables
float 

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	for(;;){
		/*
		Create a saw-tooth sound wave (range: 320Hz to 8kHz)
		Make the period and volume adjustable using the potentiometers
		*/
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
