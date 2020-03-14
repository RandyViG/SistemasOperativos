;**************************************************************
;	   	    	File Handling - Delete
;Compilar:
;	nasm -f elf lesson28.asm
;	ld -m elf_i386 lesson28.o -o lesson28
;**************************************************************
 
%include    'functions.asm'
 
SECTION .data
filename 	db 	'readme.txt', 	0x0 
 
SECTION .text
global  _start
 
_start:
 
    	mov     ebx, 	filename       
    	mov     eax, 	10             
    	int     0x80                  

    call    quit                
