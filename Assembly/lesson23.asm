;**************************************************************
;	   	    		File Handling - Write
;Compilar:
;	nasm -f elf lesson23.asm
;	ld -m elf_i386 lesson23.o -o lesson23
;**************************************************************
 
%include    'functions.asm'
 
SECTION .data
filename db 'readme.txt', 0h    
contents db 'Hello world!', 0h  
 
SECTION .text
global  _start
 
_start:
 
    mov     ecx, 0777           
    mov     ebx, filename
    mov     eax, 8
    int     80h
 
    mov     edx, 12             
    mov     ecx, contents       
    mov     ebx, eax            
    mov     eax, 4              
    int     80h                 
 
    call    quit                