
TITLE Group Project COA Group 5

INCLUDE Irvine32.inc

.data
	;	Data for main menu
	main_menu BYTE "Please select the conversion type: ", 13, 10
		BYTE "1. Binary to Decimal", 13, 10
		BYTE "2. Decimal to Binary", 13, 10
		BYTE "3. Exit", 13, 10
		BYTE "----------------------------------------------------", 13, 10, 0
	prompt BYTE "Enter your Choice: ", 0
	invalid BYTE "Invalid Choice. Please Enter Again", 13, 10, 0
	thank BYTE "Bye.", 13, 10, 0

	;	Data for Procedures
	binary_string BYTE "00000000", 0
	invalid_in BYTE "Invalid Input. Please Enter Again", 13, 10, 0
	
	prompt_decimal BYTE "Please Enter a Decimal Integer less than 256: ", 0
	d2b_res1 BYTE "The binary of ", 0
	d2b_res2 BYTE "d is ", 0

	prompt_binary BYTE "Please Enter 8-bit binary digits (e.g., 11110000): ", 0
	b2d_res1 BYTE "The decimal integer of "
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
	
	
	;	Read Input
	MOV EDX, OFFSET binary_string
	MOV ECX, 9
	CALL ReadString

	;	Input Validation
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

	;	Conversion
	CALL B2D_Converter

	;	Output
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
b2d_invalid_block:
	MOV EDX, OFFSET invalid_in
	CALL WriteString
	JMP b2d_input_block

Binary_To_Decimal ENDP


;============================================
; Converter from Binary String0 to Decimal
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
	JNE b2d_continue_block
	INC EAX
b2d_continue_block:
	INC EDI
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


	;	Input Validation
	JO d2b_invalid_block
	CMP EAX, 0
	JL d2b_invalid_block
	CMP EAX, 256
	JGE d2b_invalid_block

	;	Output
	MOV EDX, OFFSET d2b_res1
	CALL WriteString
	CALL WriteDec
	MOV EDX, OFFSET d2b_res2
	CALL WriteString

	CALL D2B_Converter
	MOV EDX, OFFSET binary_string
	CALL WriteString
	MOV AL, 'b'
	CALL WriteChar

	CALL Crlf
	CALL Crlf
	ret

d2b_invalid_block:
	MOV EDX, OFFSET invalid_in
	CALL WriteString
	JMP d2b_input_block
Decimal_To_Binary ENDP


;============================================
; Converter from Decimal to Binary String
;============================================
D2B_Converter PROC
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
	MOV EDX, OFFSET main_menu
	CALL WriteString

input_block:
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

finish_block:
	MOV EDX, OFFSET thank
	CALL WriteString
	CALL WaitMsg

	exit
main ENDP
END main        