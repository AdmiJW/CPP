
TITLE Fishing Mechanism

INCLUDE Irvine32.inc

.data
	
	prompt BYTE "Press Space when the arrow aligns with the [X]!", 13, 10, 13, 10, 0
	blocks BYTE "[ ][ ][ ][ ][ ][ ][ ][ ]", 0

.code

;--------------------------------------------
PrintArrow PROC USES EAX ECX EDX
;
; Prints out the first line: The arrow v
; Receives: EDX - The block in which the arrow should point to, starting from 0
; Returns: EAX - 1 if successful catch the fish, 0 if failed
	MOV EAX, 3
	MUL EDX
	MOV ECX, EAX
	INC ECX				;Offset by 1 to account for leftmost [

	MOV EBX, LENGTHOF blocks	;For printing post v spaces
	SUB EBX, ECX
	DEC EBX
	DEC EBX

	MOV AL, ' '
printArrow_print_spaces:
	CALL WriteChar
	LOOP printArrow_print_spaces

	MOV AL, 'v'
	CALL WriteChar

	MOV ECX, EBX
	MOV AL, ' '
printArrow_print_spaces2:
	CALL WriteChar
	LOOP printArrow_print_spaces2

	RET
PrintArrow ENDP
;--------------------------------------------


;--------------------------------------------
FishingMechanism PROC,
	Level:DWORD
	LOCAL RandomPosition:DWORD,
		  RandomNum:DWORD,
		  DelayTime:DWORD
; Receives: Level - Level 1 - 15 for fishing. Higher level, higher difficulty

	; Step 1: Generate Random Position for block
	MOV EAX, 8
	CALL Randomize
	CALL RandomRange
	MOV RandomNum, EAX
	MOV EBX, 3
	MUL EBX
	INC EAX
	MOV RandomPosition, EAX

	; Step 2: Modify block string
	MOV [blocks+EAX], 'X'
	MOV EDX, OFFSET blocks

	; Step 3: Calculate Delay Time
	MOV EAX, 40
	MUL Level
	MOV EBX, 640          ;Slowest time
	SUB EBX, EAX
	MOV DelayTime, EBX

	; Step 4: Main loop for fishing mechanism
	MOV ECX, 0

	; Print out the prompt, arrow and grid
	MOV EDX, OFFSET prompt
	CALL WriteString

	MOV EDX, ECX
	CALL PrintArrow
	CALL Crlf

	MOV EDX, OFFSET blocks
	CALL WriteString

fishing_mechanism_loop:

	;Move cursor to the arrow row
	MOV DX, 0200h
	CALL Gotoxy

	;Print arrow
	MOV EDX, ECX
	CALL PrintArrow

	;Delay time
	MOV EAX, DelayTime
	CALL Delay

	;Check if the spacebar is pressed
	CALL ReadKey
	CMP AL, 20h
	JE spacebar_pressed

	;Spacebar not pressed
	;Increment arrow position
	INC ECX
	AND ECX, 0111b

	JMP fishing_mechanism_loop

spacebar_pressed:
	CALL Clrscr

	CMP ECX, RandomNum
	JE fish_successfully_catched
	
	;Failed to catch the fish
	MOV EAX, 0
	RET

	;Success to catch the fish
fish_successfully_catched:
	MOV EAX, Level
	RET
FishingMechanism ENDP
END