;**************************************************************
;	   	    	Socket - Create
;Compilar:
;	nasm -f elf lesson29.asm
;	ld -m elf_i386 lesson29.o -o lesson29
;**************************************************************
 
%include    'functions.asm'
 
SECTION .text
global  _start
 
_start:
 
    	xor     eax, 		eax            
    	xor     ebx, 		ebx            
   	xor     edi, 		edi            
    	xor	esi, 		esi            
 
_socket:
 
    	push    byte 6              
    	push    byte 1              
    	push    byte 2              
    	mov     ecx, 		esp            
    	mov     ebx, 		1              
    	mov     eax, 		102            
    	int     0x80                 
 
    	call    iprintLF            
 
_exit:
 
    	call    quit                
