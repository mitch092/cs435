/*----------------------------------------------------------------------------
LAB EXERCISE 5.1 - PROCESSING TEXT IN ASSEMBLY LANGUAGE
 ----------------------------------------------
Examine program execution at the processor level using the debugger 
 *----------------------------------------------------------------------------*/

__asm void my_strcpy(const char *src, char *dst){
loop
		LDRB r2, [r0] ; Load byte into r2 from mem. pointed to by r0 (src pointer)
		ADDS r0, #1 ; Increment src pointer
		STRB r2, [r1] ; Store byte in r2 into memory pointed to by (dst pointer)
		ADDS r1, #1 ; Increment dst pointer
		CMP r2, #0 ; Was the byte 0?
		BNE loop ; If not, repeat the loop
		BX lr
}

__asm void my_capitalize(char *str){
cap_loop
		LDRB r1, [r0] ; Load byte into r1 from memory pointed to by r0 (str pointer)
		CMP r1, #'a'-1 ; compare it with the character before 'a'
		BLS cap_skip ; If byte is lower or same, then skip this byte
		CMP r1, #'z' ; Compare it with the 'z' character
		BHI cap_skip ; If it is higher, then skip this byte
		SUBS r1,#32 ; Else subtract out difference to capitalize it
		STRB r1, [r0] ; Store the capitalized byte back in memory
cap_skip
		ADDS r0, r0, #1 ; Increment str pointer
		CMP r1, #0 ; Was the byte 0?
 		BNE cap_loop ; If not, repeat the loop
		BX lr ; Else return from subroutine
}

__asm void my_downcase(char *str){
down_loop
		LDRB r1, [r0] ; Load byte into r1 from memory pointed to by r0 (str pointer)
		CMP r1, #'A'-1 ; compare it with the character before 'A'
		BLS down_skip ; If byte is lower or same, then skip this byte
		CMP r1, #'Z' ; Compare it with the 'Z' character
		BHI down_skip ; If it is higher, then skip this byte
		ADDS r1,#32 ; Else add 32 to downcase the character.
		STRB r1, [r0] ; Store the downcased byte back in memory
down_skip
		ADDS r0, r0, #1 ; Increment str pointer
		CMP r1, #0 ; Was the byte 0?
 		BNE down_loop ; If not, repeat the loop
		BX lr ; Else return from subroutine
}

__asm void my_first_last_cap(char *str){	
// r0 contains the current pointer to the str
// r1 contains the dereferenced value of r0
// r2 contains the memory address of the first element in str
	
		MOV r2, r0
	
		// If we've reached the end of the string. Jump to the third loop in this case.
fl_first_loop
		LDRB r1, [r0]
		CMP r1, #0
		BEQ fl_third_loop

		// If the char is a lowercase letter, uppercase it and go to the second loop.
		// Otherwise, increment the pointer and go back to the first loop.
		CMP r1, #'a'-1 
		BLS fl_first_loop_increment
		CMP r1, #'z' 
		BHI fl_first_loop_increment

		B fl_first_loop_uppercase
	
		// Go directly to the second loop if we find an uppercase letter.
		CMP r1, #'A'-1 
		BLS  fl_first_loop_increment
		CMP r1, #'Z' 
		BHI  fl_first_loop_increment

		B fl_second_loop
	
fl_first_loop_increment
		ADDS r0, r0, #1
		B fl_first_loop
	
	
fl_first_loop_uppercase
		SUBS r1,#32
		STRB r1, [r0]		
		

// In the second loop, find the end of the string (null terminator).
fl_second_loop
		LDRB r1, [r0]
		CMP r1, #0
		BEQ fl_third_loop
		
		ADDS r0, r0, #1
		B fl_second_loop
		

	
// The third loop is exactly like the first loop, except in reverse.
// And instead of stopping on null terminator, we stop on the value in r2.
fl_third_loop
		CMP r0, r2
		BEQ fl_end
		LDRB r1, [r0]


		// If the char is a lowercase letter, uppercase it and go to the second loop.
		// Otherwise, increment the pointer and go back to the first loop.
		CMP r1, #'a'-1 
		BLS fl_third_loop_increment
		CMP r1, #'z' 
		BHI fl_third_loop_increment

		B fl_third_loop_uppercase
	
		// Go directly to the second loop if we find an uppercase letter.
		CMP r1, #'A'-1 
		BLS  fl_third_loop_increment
		CMP r1, #'Z' 
		BHI  fl_third_loop_increment

		B fl_end
	
fl_third_loop_increment
		SUBS r0, r0, #1
		B fl_third_loop
	
	
fl_third_loop_uppercase
		SUBS r1,#32
		STRB r1, [r0]	
	
fl_end	
	
		BX lr
}


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(void){
	const char a[] = "Hello world!";
	char b[20];
	my_strcpy(a,b);
	my_capitalize(b);
	
	
	
	// Test data for my_downcase():
	
	char test1[] = "hello world";
	char test2[] = "HELLO WORLD!";
	char test3[] = "hElLo WoRlD!";
	char test4[] = "1H2E3L4L5O";
	char test5[] = "!@#$%^&*()=+[]{};':\",.<>/?";

	char test6[] = "a123 ()*& xyz";
	char test7[] = "12345";
	char test8[] = "123h456e789";
	char test9[] = "K{[])90t";
	char test10[] = "123aaa33aa333aa33aa321";
	
	my_downcase(test1);
	my_downcase(test2);
	my_downcase(test3);
	my_downcase(test4);
	my_downcase(test5);
	
	my_first_last_cap(test6);
	my_first_last_cap(test7);
	my_first_last_cap(test8);
	my_first_last_cap(test9);
	my_first_last_cap(test10);

	
	
	
	
	
	for(;;);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
