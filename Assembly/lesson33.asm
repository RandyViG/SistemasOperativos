;**************************************************************
;	   	    	   Socket - Read
;Compilar:
;	nasm -f elf lesson33.asm
;	ld -m elf_i386 lesson33.o -o lesson33
;**************************************************************
 
%include    'functions.asm'
 
SECTION .bss
buffer	resb 	255                
 
SECTION .text
global  _start
 
_start:
 
    	xor     eax, 		eax            
    	xor     ebx, 		ebx
    	xor     edi, 		edi
    	xor     esi, 		esi
 
_socket:
 
    	push    byte 6              
    	push    byte 1
    	push    byte 2
    	mov     ecx, 		esp
    	mov     ebx, 		1
    	mov     eax, 		102
    	int     0x80
 
_bind:
 
    	mov     edi, 		eax            
    	push    dword 0x00000000
    	push    word 0x2923
    	push    word 2
    	mov     ecx, 		esp
    	push    byte 16
        push    ecx
    	push    edi
    	mov     ecx,	 	esp
    	mov     ebx, 		2
    	mov     eax, 		102
    	int     0x80
 
_listen:
 
    	push    byte 1              
    	push    edi
    	mov     ecx, 		esp
    	mov     ebx, 		4
    	mov     eax, 		102
    	int     0x80
 
_accept:
 
    	push    byte 0              
    	push    byte 0
    	push    edi
    	mov     ecx, 		esp
    	mov     ebx, 		5
    	mov     eax, 		102
    	int     0x80

_fork:
 
    	mov     esi,		eax            
    	mov     eax, 		2              
    	int     0x80    
 
    	cmp     eax, 		0              
    	jz      _read               
 
    	jmp     _accept             
 
_read:
 
    	mov     edx, 		255            
    	mov     ecx, 		buffer         
    	mov     ebx, 		esi            
    	mov     eax, 		3              
    	int     0x80                 
 
    	mov     eax, 		buffer         
    	call    sprintLF            
 
_exit:
 
    	call    quit                
