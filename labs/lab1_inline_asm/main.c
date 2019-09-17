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
		; Make sure that the first byte is not the null terminator, otherwise do nothing.
		LDRB r1, [r0]
		CMP r1, #0
		BEQ fl_cap_end
	
		; Now if we are here, then that means that the first char is not '\0'.
		; So now check to see if this byte is between 'a' and 'z'.
fl_upper_case
		CMP r1, #'a'-1
		BLS fl_cap_skip
		CMP r1, #'z'
		BHI fl_cap_skip	
		
		; If the byte is a lower case ascii char, subtract 32 and store it back in its buffer.
		SUBS r1,#32
		STRB r1, [r0]
		
fl_cap_skip
		; Get the current byte and the byte after the current byte.
		LDRB r1, [r0]
		LDRB r2, [r0, #1] 
		; Was the next byte the null terminator?
		CMP r2, #0
		; If it was, then this is the last byte. Get it, uppercase it and end.
		BEQ fl_upper_case2
		; Otherwise, increment the string pointer and re-run this loop.
		ADDS r0, r0, #1
		B fl_cap_skip		
		
fl_upper_case2
		CMP r1, #'a'-1
		BLS fl_cap_end
		CMP r1, #'z'
		BHI fl_cap_end	
		
		; If the byte is a lower case ascii char, subtract 32 and store it back in its buffer.
		SUBS r1,#32
		STRB r1, [r0]		
	
fl_cap_end
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
	char test4[] = "";
	char test5[] = "!@#$%^&*()=+[]{};':\",.<>/?";

	char test6[] = "a123 ()*& xyz";
	char test7[] = "12345";
	char test8[] = "";
	char test9[] = "K{[])90t";
	char test10[] = "aaaaaaaaa";
	
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
