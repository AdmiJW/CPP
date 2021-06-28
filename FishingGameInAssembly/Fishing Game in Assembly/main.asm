
INCLUDE Irvine32.inc
INCLUDE include.inc

.data
myList DWORD 2, 3, 5, 8

.code
main PROC
  

  CALL Fish_Show

  exit
main ENDP

END main        ;specify the program's entry point