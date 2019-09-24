/*----------------------------------------------------------------------------
LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
 ----------------------------------------
Write an assembly code subroutine to approximate the square root of an 
argument using the bisection method. All math is done with integers, so the 
resulting square root will also be an integer

GOOD LUCK!
 *----------------------------------------------------------------------------*/

// I made the input and output to be unsigned integers,
// because the square root of any negative number
// is a complex number. Complex numbers
// are outside the scope of my sqrt subroutine,
// so I am using the types to document that.
__asm unsigned int my_sqrt(unsigned int x){
	// According to the calling conventions,
	// the registers that I am allowed to use are
	// r4 to r11. They must be saved before I use them 
	// and restored after I'm done using them.
	// I'm not using r11, so ignore it.
	PUSH {r4-r10}	
	
	// r4 contains x
	// r5 contains a
	// r6 contains b
	// r7 contains c
	// r8 contains c_old
	// r9 contains c_squared
	// r10 is used to store 2 for the division.	
	
	// There is only one argument for this subroutine.
	// Move it into the first register that I am allowed to use,
	// according to the calling convention.
	MOV r4, r0
	
	// a = 0
	MOV r5, #0
	// b = sqrt(2^32) = 2^16 = 65536 = 0x00010000
	LDR r6, =0x00010000
	// I have made the default return value to be 0, so c = 0.
	MOV r7, #0
	
my_sqrt_loop
	// c_old = c
  MOV r8, r7
	// c = a+b
	ADD r7, r5, r6
	// c = c/2; must store the 2 in a register 
	// because immediates are not allowed for UDIV.
	MOV r10, #2
	UDIV r7, r7, r10
	// c_squared = c * c
	MUL r9, r7, r7
	// Set the conditional flags
	// for the calculation c_squared - x
	CMP r9, r4
	// if (c_squared < x) a = c; 
	MOVLO r5, r7
	// else if (c_squared > x) b = c; 
	MOVHI r6, r7
	// If c_squared == x, then we are done. Branch to the end.
	BEQ my_sqrt_end
	// Otherwise, branch to the loop if (c != c_old)
	CMP r7, r8
	BNE my_sqrt_loop
	
my_sqrt_end
  // Move c into the return register r0.
	MOV r0, r7
	// Restore r4-r10.
	POP {r4-r10}
	// Return.
	BX lr;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(void){
	volatile int r, j=0;
	int i;
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
