/*----------------------------------------------------------------------------
LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
 ----------------------------------------
Write an assembly code subroutine to approximate the square root of an 
argument using the bisection method. All math is done with integers, so the 
resulting square root will also be an integer

GOOD LUCK!
 *----------------------------------------------------------------------------*/

__asm int my_sqrt(int x){
	// r0 contains x
	// r1 contains a
	// r2 contains b
	// r3 contains c
	// r4 contains c_old
	// r5 contains c_squared
	// r6 is temporarily used to store 2 for the division.
	
	// a = 0
	MOV r1, #0
	// b = sqrt(2^32) = 2^16 = 65536 = 0x00010000
	LDR r2, =0x00010000
	// c = -1
	MOV r3, #-1
	
my_sqrt_loop
	// c_old = c
  MOV r4, r3
	// c = a+b
	ADD r3, r1, r2
	// c = c/2; must store the 2 in a temporary register 
	// because immediates are not allowed for UDIV
	MOV r6, #2
	UDIV r3, r3, r6
	// c_squared = c * c
	MUL r5, r3, r3
	// Set the conditional flags
	// for the calculation c_squared - x
	CMP r5, r0
	// if (c_squared < x) a = c; 
	MOVLO r1, r3
	// else if (c_squared > x) b = c; 
	MOVHI r2, r3
	// If c_squared == x, then we are done. Branch to the end.
	BEQ my_sqrt_end
	// Otherwise, branch to the loop if (c != c_old)
	CMP r3, r4
	BNE my_sqrt_loop
	
my_sqrt_end
  // Move c into the return register r0 and return.
	MOV r0, r3
	BX lr;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(void){
	volatile int r, j=0;
	volatile int i;
  r = my_sqrt(0);     // should be 0
  r = my_sqrt(25);    // should be 5
	r = my_sqrt(133); 	// should be 11
  for (i=0; i<10000; ++i){
		r = my_sqrt(i);
    j+=r;
  }
	

	for(;;);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
