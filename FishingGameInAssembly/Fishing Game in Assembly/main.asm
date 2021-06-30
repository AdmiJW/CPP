
INCLUDE Irvine32.inc
INCLUDE include.inc

.data
	;Player Stats
	Money DWORD 0
	Level DWORD 1
	NextLevel DWORD 0, 10, 25, 50, 75, 100, 150, 200, 350, 500, 750, 900, 1250, 2500, 5000, 8000
	Buff DWORD 0
	Bait DWORD 0
	CurrFishRodAddr DWORD ?

	; Fishing Rods
	Wood_FR BYTE "Wooden Fishing Rod", 0
	Iron_FR BYTE "Iron Fishing Rod", 0
	Rein_FR BYTE "Reinforced Fishing Rod", 0
	Silver_FR BYTE "Silver Fishing Rod", 0
	Carbon_FR BYTE "Carbon Fiber Fishing Rod", 0
	Gold_FR BYTE "Golden Fishing Rod", 0

	Main_Menu BYTE "==============================", 13, 10
		BYTE "		MAIN MENU		", 13, 10
		BYTE "==============================", 13, 10
		BYTE "1 - Go Fishing", 13, 10
		BYTE "2 - Shop", 13, 10
		BYTE "3 - Exit Game", 13, 10, 0
	Shop_Menu BYTE "==============================", 13, 10
		BYTE "		Shop		", 13, 10
		BYTE "==============================", 13, 10
		BYTE "1 - Bait ($20) - One time use only, Power+1", 13, 10
		BYTE "2 - Iron Fishing Rod ($100) - Power+1", 13, 10
		BYTE "3 - Reinforced Fishing Rod ($250) - Power+2", 13, 10
		BYTE "4 - Silver Fishing Rod ($700) - Power+3", 13, 10
		BYTE "5 - Carbon Fiber Fishing Rod ($1000) - Power+4", 13, 10
		BYTE "6 - Golden Fishing Rod ($3000) - Power+5", 13, 10, 
		BYTE "7 - Exit Shop", 13, 10, 13, 10, 0

	Prompt_Choice BYTE "Enter your choice: ", 0

	Invalid_Input BYTE "Invalid choice. Enter Again: ", 0
	
	Stats_1 BYTE "<Your Stats>", 13, 10
		BYTE "Money: ", 0
	Stats_2 BYTE 13, 10, "Level: ", 0
	Stats_3 BYTE 13, 10, "Experience: ", 0
	Stats_4 BYTE 13, 10, "Bait: ", 0
	Stats_5 BYTE 13, 10, "Fishing Rod: ", 0


;	lvl0 - 10
;	lvl1 - 25
;	lvl2 - 50
;	lvl3 - 75
;	lvl4 - 100
;	lvl5 - 150
;	lvl6 - 200
;	lvl7 - 350
;	lvl8 - 500
;	lvl9 - 750
;	lvl10 - 900
;	lvl11 - 1250
;	lvl12 - 2000
;	lvl13 - 3000
;	lvl14 - 5000
;	lvl15 - 8000
;		Increment 2000

.code
main PROC
  

  INVOKE Fish_Show, 11

  exit
main ENDP

END main        ;specify the program's entry point