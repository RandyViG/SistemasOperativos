;**************************************************************
;	   	         Download a Webpage
;Compilar:
;	nasm -f elf lesson36.asm
;	ld -m elf_i386 lesson36.o -o lesson36
;**************************************************************
 
%include    'functions.asm'
 
SECTION .data
; our request string
request db 'GET / HTTP/1.1', 0Dh, 0Ah, 'Host: 139.162.39.66:80', 0Dh, 0Ah, 0Dh, 0Ah, 0h
 
SECTION .bss
buffer 	resb 	1                  
 
SECTION .text
global  _start
 
_start:
 
    	xor     eax, 		eax            
    	xor     ebx, 		ebx            
    	xor     edi, 		edi            
 
_socket:
 
    	push    byte 6              
    	push    byte 1              
    	push    byte 2              
    	mov     ecx, 		esp            
    	mov     ebx, 		1              
    	mov     eax, 		102           
    	int     0x80                 

_connect:
 
   	mov     edi, 		eax            
    	push    dword 0x4227a28b    
    	push    word 0x5000         
    	push    word 2              
    	mov     ecx, 		esp            
    	push    byte 16             
    	push    ecx                 
    	push    edi                 
    	mov     ecx, 		esp            
    	mov     ebx, 		3              
    	mov     eax, 		102            
    	int     0x80                 
 
_write:
 
    	mov     edx, 		43             
    	mov     ecx, 		request        
    	mov     ebx, 		edi            
    	mov     eax, 		4              
    	int     0x80                 
 
_read:
 
    	mov     edx, 		1              
    	mov     ecx, 		buffer         
    	mov     ebx, 		edi            
    	mov     eax, 		3	              
    	int     0x80                 
 
    	cmp     eax, 		0              
    	jz      _close              
 
    	mov     eax, 		buffer         
    	call    sprint              
    	jmp     _read               

_close:
 
    	mov     ebx, 		edi            
    	mov     eax, 		6              
    	int     0x80                 
 
_exit:
 
    	call    quit                
