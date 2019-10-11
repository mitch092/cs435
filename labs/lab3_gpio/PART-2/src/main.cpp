/*----------------------------------------------------------------------------
LAB EXERCISE - DIGITAL INPUTS AND OUTPUTS
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define BusIn, BusOut interfaces for inputs and outputs
	2) The RGB LED is controlled by the buttons:
			+ Button 1 - light RED
			+ Button 2 - light BLUE
			+ Button 3 - light GREEN
			+ Button 4 - light WHITE (RED, GREEN and BLUE at the same time)
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"

//Define input bus
	//Write your code here
	
	// Buttons: 4, 3, 2, 1
	BusIn switches(PA_10, PB_3, PB_5, PB_4);

  // Map the name of the switch to its location in the bus.
	enum Button {
		button1 = 0,
		button2 = 1,
		button3 = 2,
		button4 = 3
	};
	
	bool button_pressed(Button button){
		return (((switches.read() >> button) & 1) == 0);
	}
	bool button_pressed(int button){
		return (((switches.read() >> button) & 1) == 0);
	}

//Define output bus for the RGB LED
	//Write your code here
	
	// LEDs: blue, green, red
	BusOut LED(PB_10, PA_8, PA_9);
	
	// Map the name of the output LED to its location in the bus.
	enum Color {
		red   = 0,
		green = 1,
		blue  = 2,
		all = 3
	};
	
	// Toggle the individual bit for an led, in the bus.
	void toggle_led(Color color){
		LED = LED ^ (1 << color);
	}
	void toggle_led(int color){
		LED = LED ^ (1 << color);
	}
	void toggle_led_all(){
		toggle_led(red);
		toggle_led(green);
		toggle_led(blue);
	}
	
	void toggle_led2(int color){
		if(color == 3) toggle_led_all();
		else toggle_led(color);
	}
	
	void part1(){
		
		//ButtonFSM fsm1, fsm2, fsm3, fsm4;

		for(;;){		
		  //Check which button was pressed and light up the corresponding LEDs
		  //Write your code here
		  if (button_pressed(button1)){
			  toggle_led(red);
				wait(0.25);
		  }
		  if (button_pressed(button2)){
			  toggle_led(green);
					wait(0.25);
		  }
		  if (button_pressed(button3)){
			  toggle_led(blue);
					wait(0.25);
		  }
		  if (button_pressed(button4)){
			  toggle_led_all();
					wait(0.25);
		  }
	  }
  }
	
	void part2(){
		//int r = 0, g = 0, b = 0, a = 0;
		bool last_pressed[] = {false, false, false, false};
		int counters[] = {0, 0, 0, 0};
		
		for(;;){					
			for(int i = 0; i != 4; ++i){
			  if(last_pressed[i] == false && button_pressed(i) == true){
					counters[i]++;
				  last_pressed[i] = true;
				  wait(0.10);
			  }
			  if(button_pressed(i) == false){
				  last_pressed[i] = false;
			  }
				if(counters[i] == 10){
				  counters[i] = 0;
				  toggle_led2(i);
			  }
			}			
	  }
	}
	


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	//part1();
	part2();
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
