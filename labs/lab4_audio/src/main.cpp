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

// For the resolution, dividing the maximum PWM timing frequency (which I am assuming is the CPU clock cycle time)
// by the highest frequency that I will output, and then inverting that, will tell me exactly how many steps
// I have in order to build my waveforms. This is the amount to increment by in the bottom for loop.
const float MIN_FREQ =  320.0f, 
	          MAX_FREQ = 8000.0f,
            RESOLUTION = static_cast<float>(1.0 / (static_cast<double>(SystemCoreClock) / MAX_FREQ)),
						BOTTOM_OFFSET = 0.022f;

// There is an issue with my potentiometers where the bottom bounds is 0.022f instead of just 0.0f.
// The upper bound is 1.0f like it should be. 
// This function applies the necessary transformations in order to get the frequency to go all the way
// down to 320 hz and also allow the volume to go all the way down to zero.
float fix_bottom_bounds_on_pot(float in, float offset){
	return (in - offset) / (1.0f - offset);
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	float i, pot1_current, pot1_last, pot2_current;
	pot1_current = pot1_last = fix_bottom_bounds_on_pot(pot1.read(), BOTTOM_OFFSET);
		
	for(;;){	  
		/*
		Create a saw-tooth sound wave (range: 320Hz to 8kHz)
		Make the period and volume adjustable using the potentiometers
		*/
		pot1_current = fix_bottom_bounds_on_pot(pot1.read(), BOTTOM_OFFSET);
		pot2_current = fix_bottom_bounds_on_pot(pot2.read(), BOTTOM_OFFSET);
		
		// For figuring out if I've fixed the potentiometer offset issue.
	  // This should show up as 320 hz in the debugger when the freq. pot is at the lowest position.
		//volatile float debug_freq = ((pot1_current * (MAX_FREQ - MIN_FREQ)) + MIN_FREQ);
		
		// If the current position of the frequency potentiometer is greater than 10% or less than 10% of its last value,
		// then update the frequency (period). This divides the range of pitches into discrete values, which is faster
		// than updating the period every loop iteration in order to get continuous values. If I don't do this, then the
		// output gets very jittery and sounds noisy. This is like button debouncing, but for potentiometers.
		if((pot1_current > (pot1_last * 1.10f)) || (pot1_current < (pot1_last * 0.90f))){						
			pot1_last = pot1_current;
			out.period(1.0f / ((pot1_current * (MAX_FREQ - MIN_FREQ)) + MIN_FREQ));
		}
		// For the volume potentiometer, I simply limit the duty cycle.
		// I also chop the duty cycle's increment step into the highest possible value
		// for this particular CPU, which is running at 84 megahertz. I'm not sure,
		// but I'm hoping that the PWM pin is in fact able to update that many times per second.
		//for(i = 0.0f; i < (0.5f * pot2_current); i += (RESOLUTION * pot2_current * 0.5f)){
		for(i = 0.0f; i < (1.0f * pot2_current); i += (RESOLUTION * pot2_current)){

			// Sawtooth:
			out = i; 
			// Sine (just to hear what it sounds like):
			//out = ((sinf(6.28318530718f * i) + 1)/2.0f);
	  }
	}	
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
