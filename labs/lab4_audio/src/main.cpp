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
	          MAX_FREQ = 8000.0f,
            RESOLUTION = 0.0001f;

void sawtooth(float volume_percent, float resolution, PwmOut& out){
	float i;
  for(i = 0.0f; i < (1.0f * volume_percent); i += (resolution * volume_percent)){	
			out = i; 
	}
}

void sine(float volume_percent, float resolution, PwmOut& out){
	float i;
  for(i = 0.0f; i < (1.0f * volume_percent); i += (resolution * volume_percent)){
		out = (sinf(6.28318530718f * i) + 1)/2.0f;
  }
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	float pot1_current, pot1_last;
	pot1_current = pot1_last = pot1.read();	
	
	float pot2_current;
	
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
		
		//sawtooth(pot2_current, RESOLUTION, out);
		sine(pot2_current, RESOLUTION, out);
	}	
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
