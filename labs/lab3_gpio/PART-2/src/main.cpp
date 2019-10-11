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
	
	class ButtonFSM{
		public:
		ButtonFSM() : last_press(false){}
		bool operator()(Button button){
			// Read the individual bit in the bus.
			bool pressed = button_pressed(button);			
			
			if(last_press == true){
				if(pressed == true){
           last_press = false;
				} else {
					last_press = false;
				}
			} else {
				if(pressed == true){
					last_press = true;
				} else {
					last_press = false;
				}
			}
			return last_press;			
		}
		
		private:
			bool last_press;
	};

//Define output bus for the RGB LED
	//Write your code here
	
	// LEDs: blue, green, red
	BusOut LED(PB_10, PA_8, PA_9);
	
	// Map the name of the output LED to its location in the bus.
	enum Color {
		red   = 0,
		green = 1,
		blue  = 2
	};
	
	// Toggle the individual bit for an led, in the bus.
	void toggle_led(Color color){
		LED = LED ^ (1 << color);
	}
	void toggle_led_all(){
		toggle_led(red);
		toggle_led(green);
		toggle_led(blue);
	}
	
	/*void part1(){
		
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
  }*/
	
	void part2(){
		int r = 0, g = 0, b = 0, a = 0;
		//ButtonFSM fsm1, fsm2, fsm3, fsm4;
		
		for(;;){		
		  if (button_pressed(button1)){
			  ++r;
				wait(0.25);
		  }
		  else if (button_pressed(button2)){
			  ++g;				
				wait(0.25);
		  }
		  else if (button_pressed(button3)){
			  ++b;				
				wait(0.25);
		  }
		  else if (button_pressed(button4)){
			  ++a;
   			wait(0.25);

		  }
			
			if(r == 10){
				r = 0;
				toggle_led(red);
				wait(0.25);
			}
			if(g == 10){
				g = 0;
			  toggle_led(green);
				wait(0.25);
			}
			if(b == 10){
				b = 0;
				toggle_led(blue);
				wait(0.25);
			}
			if(a == 10){
				a = 0;
				toggle_led_all();
				wait(0.25);
			}
	  }
	}
	


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	part2();
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
