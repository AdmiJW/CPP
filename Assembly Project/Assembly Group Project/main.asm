
TITLE Group Project COA Group 5

INCLUDE Irvine32.inc

.data
	;	Strings for main menu
	main_menu BYTE "Please select the conversion type: ", 13, 10
		BYTE "1. Binary to Decimal", 13, 10
		BYTE "2. Decimal to Binary", 13, 10
		BYTE "3. Exit", 13, 10
		BYTE "----------------------------------------------------", 13, 10, 0
	prompt BYTE "Enter your Choice: ", 0
	invalid BYTE "Invalid Choice. Please Enter Again", 13, 10, 0
	thank BYTE "Bye.", 13, 10, 0

	;	Strings for Operations.
	binary_string BYTE "00000000", 0									;Stores 8 character strings representing the binary 8 bits
	decimal_num DWORD ?													;Stores the decimal number user inputted
	invalid_in BYTE "Invalid Input. Please Enter Again", 13, 10, 0		;Invalid input message
	
	;	Strings for Function 1 - Decimal to Binary
	prompt_decimal BYTE "Please Enter a Decimal Integer less than 256: ", 0
	d2b_res1 BYTE "The binary of ", 0
	d2b_res2 BYTE "d is ", 0

	;	Strings for Function 2 - Binary to Decimal
	prompt_binary BYTE "Please Enter 8-bit binary digits (e.g., 11110000): ", 0
	b2d_res1 BYTE "The decimal integer of ", 0
	b2d_res2 BYTE "b is ", 0


.code
;============================================
; Binary to Decimal Conversion Procedure
;============================================
Binary_To_Decimal PROC

b2d_input_block:
	;	Prompt Message
	MOV EDX, OFFSET prompt_binary
	CALL WriteString
	
	;	Read Input from user
	MOV EDX, OFFSET binary_string
	MOV ECX, 9
	CALL ReadString

	;	Input Validation. Use loop to check whether the 8 characters inputted is either '0' or '1' only
	MOV ECX, 8
	MOV ESI, 0
	MOV BH, "1"		; Test bits
	MOV BL, "0"
b2d_validation_block:
	CMP [binary_string + ESI], BH
	JE b2d_valid_block
	CMP [binary_string + ESI], BL
	JE b2d_valid_block
	JMP b2d_invalid_block
b2d_valid_block:
	INC ESI
	LOOP b2d_validation_block

	;	Perform Conversion - Magic Function
	CALL B2D_Converter

	;	Output the Conversion Result
	MOV EDX, OFFSET b2d_res1
	CALL WriteString
	MOV EDX, OFFSET binary_string           
	CALL WriteString
	MOV EDX, OFFSET b2d_res2
	CALL WriteString
	CALL WriteDec
	MOV AL, 'd'
	CALL WriteChar

	CALL Crlf
	CALL Crlf

	ret

	;Jumps to here when user enter invalid binary string. Prompt user to enter again
b2d_invalid_block:
	MOV EDX, OFFSET invalid_in
	CALL WriteString
	JMP b2d_input_block

Binary_To_Decimal ENDP


;============================================
; Converter from Binary String to Decimal
;
; Converts by checking each bit, multiply 2 and increment 1 method
;============================================
B2D_Converter PROC
	MOV ECX, 8
	MOV EDI, 0
	MOV EAX, 0
	MOV BL, "1"
	MOV BH, 2
b2d_check_block:
	MUL BH

	CMP [binary_string+EDI], BL
	JNE b2d_continue_block				;Do not add 1 if bit is '0'
	INC EAX
b2d_continue_block:
	INC EDI								;Add 1 if bit is '1'
	LOOP b2d_check_block

	ret
B2D_Converter ENDP



;============================================
; Decimal to Binary Conversion Procedure
;============================================
Decimal_To_Binary PROC

d2b_input_block:
	;	Prompt Message
	MOV EDX, OFFSET prompt_decimal
	CALL WriteString

	;	Read Input from user. - Reads a decimal number
	CALL ReadInt

	;	Input Validation. Checks if the input is in range 0-255. If out of range, invalid input
	JO d2b_invalid_block
	CMP EAX, 0
	JL d2b_invalid_block
	CMP EAX, 256
	JGE d2b_invalid_block

	MOV decimal_num, EAX

	;	Conversion - magic function
	CALL D2B_Converter

	;	Output the result of conversion
	MOV EDX, OFFSET d2b_res1
	CALL WriteString
	MOV EAX, decimal_num
	CALL WriteDec
	MOV EDX, OFFSET d2b_res2
	CALL WriteString

	MOV EDX, OFFSET binary_string
	CALL WriteString
	MOV AL, 'b'
	CALL WriteChar

	CALL Crlf
	CALL Crlf
	RET

	;Jumps here when user input is invalid (Out of range 0-255)
d2b_invalid_block:
	MOV EDX, OFFSET invalid_in
	CALL WriteString
	JMP d2b_input_block
Decimal_To_Binary ENDP


;============================================
; Converter from Decimal to Binary String
;
; Converts by repeatedly dividing 2 and obtain remainder, just like Semester 1 Digital Logic
;============================================
D2B_Converter PROC
	MOV EAX, decimal_num
	MOV EDI, 7		;	Binary String index in 'binary_string'
	MOV ECX, 8		;	Loop counter
	MOV BL, 2		;	Divisor
	
d2b_division:
	DIV BL
	TEST AH, 1
	JNZ d2b_remainder1

	MOV [binary_string + EDI], '0'
	JMP d2b_continue
	
d2b_remainder1:
	MOV [binary_string + EDI], '1'

d2b_continue:
	MOV AH, 0
	DEC EDI
	LOOP d2b_division

	ret 
D2B_Converter ENDP


;=================================
; Main Procedure. Handles Menu 
;=================================
main PROC
	
main_menu_block:
	;Prints main menu
	MOV EDX, OFFSET main_menu
	CALL WriteString

input_block:
	;Obtain user choice for menu: 1 for binary to decimal etc...
	MOV EDX, OFFSET prompt
	CALL WriteString
	CALL ReadInt

	JO invalid_choice_block

	CMP EAX, 1
	JE binary_to_decimal_block
	CMP EAX, 2
	JE decimal_to_binary_block
	CMP EAX, 3
	JE finish_block

	JMP invalid_choice_block

	;Invalid menu choice
invalid_choice_block:
	MOV EDX, OFFSET invalid
	CALL WriteString
	JMP input_block

binary_to_decimal_block:
	CALL Binary_To_Decimal
	JMP main_menu_block

decimal_to_binary_block:
	CALL Decimal_To_Binary
	JMP main_menu_block

	;User selects to exit the program. Print Bye
finish_block:
	MOV EDX, OFFSET thank
	CALL WriteString
	CALL WaitMsg

	exit
main ENDP
END main        