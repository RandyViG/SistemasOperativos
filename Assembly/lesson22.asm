;**************************************************************
;	   	    		   File Handling - Create
;Compilar:
;	nasm -f elf lesson22.asm
;	ld -m elf_i386 lesson22.o -o lesson22
;**************************************************************

%include    'functions.asm'
 
SECTION .data
filename db 'readme.txt',       
 
SECTION .text
global  _start
 
_start:
 
    mov     ecx, 	0777           
    mov     ebx, 	filename       
    mov     eax, 	8              
    int     80h                 
 
    call    quit                
