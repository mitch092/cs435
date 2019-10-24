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
const float MIN_FREQ =  320.0f, 
	          MAX_FREQ = 8000.0f;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	float i;
	
	float pot1_current, pot1_last;
	pot1_current = pot1_last = pot1.read();	
	
	float pot2_current;
	
	out.period(1.0f / ((pot1_last * (MAX_FREQ - MIN_FREQ)) + MIN_FREQ));

	for(;;){	  
		/*
		Create a saw-tooth sound wave (range: 320Hz to 8kHz)
		Make the period and volume adjustable using the potentiometers
		*/
		pot1_current = pot1.read();
		pot2_current = pot2.read();
		
		if((pot1_current > (pot1_last * 1.10f)) || (pot1_current < (pot1_last * 0.90f))){
			pot1_last = pot1_current;		
			out.period(1.0f / ((pot1_current * (MAX_FREQ - MIN_FREQ)) + MIN_FREQ));
		}
		
		for(i = 0.0f; i < 1.0f; i += 0.005f){
			out = i * pot2_current; 
		}
	}	
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
