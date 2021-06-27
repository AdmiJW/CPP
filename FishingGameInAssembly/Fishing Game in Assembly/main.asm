
INCLUDE Irvine32.inc
INCLUDE include.inc

.data
myList DWORD 2, 3, 5, 8

.code
main PROC
  

  INVOKE FishingMechanism, 15

  exit
main ENDP

END main        ;specify the program's entry point