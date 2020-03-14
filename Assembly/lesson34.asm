;**************************************************************
;	   	    	 Socket - Write
;Compilar:
;	nasm -f elf lesson34.asm
;	ld -m elf_i386 lesson34.o -o lesson34
;**************************************************************
 
%include    'functions.asm'
 
SECTION .data
; our response string
response db 'HTTP/1.1 200 OK', 0Dh, 0Ah, 'Content-Type: text/html', 0Dh, 0Ah, 'Content-Length: 14', 0Dh, 0Ah, 0Dh, 0Ah, 'Hello World!', 0Dh, 0Ah, 0h
 
SECTION .bss
buffer 	resb 	255                
 
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
    	mov     ecx, 		esp
    	mov     ebx, 		2
    	mov     eax, 		102
    	int     0x80

_listen:
 
    	push    byte 1              
    	push    edi
    	mov     ecx, 		esp
    	mov     ebx, 		4
    	mov     eax, 		102
    	int     80h
 
_accept:
 
    	push    byte 0              
    	push    byte 0
    	push    edi
    	mov     ecx, 		esp
    	mov     ebx, 		5
    	mov     eax, 		102
    	int     0x80
 
_fork:
 
    	mov     esi, 		eax           
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

write:
 
    	mov     edx, 		78             
    	mov     ecx, 		response       
    	mov     ebx, 		esi            
    	mov     eax, 		4              
    	int     0x80                 
 
_exit:
 
    	call    quit              
    
