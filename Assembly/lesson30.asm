;**************************************************************
;	   	  	   Socket - Bind
;Compilar:
;	nasm -f elf lesson30.asm
;	ld -m elf_i386 lesson30.o -o lesson30
;**************************************************************
 
%include    'functions.asm'
 
SECTION .text
global  _start
 
_start:
 
    	xor     eax, 		eax            
    	xor     ebx, 		ebx
    	xor     edi, 		edi
    	xor     esi,		esi
 
_socket:
 
    	push    byte 6              
    	push    byte 1
    	push    byte 2
    	mov     ecx, 		esp
    	mov     ebx, 		1
    	mov     eax, 		102
    	int     0x80
 
_bind:
 
    	mov	edi,	 	eax            
    	push    dword 0x00000000    
    	push    word 0x2923         
    	push    word 2              
    	mov     ecx, 		esp            
    	push    byte 16             
   	push    ecx                 
    	push    edi                 
    	mov     ecx, 		esp            
    	mov     ebx, 		2              
    	mov     eax, 		102            
    	int     0x80                 
 
_exit:
 
    	call    quit                
