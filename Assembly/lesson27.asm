;**************************************************************
;	   	    	File Handling - Update
;Compilar:
;	nasm -f elf lesson27.asm
;	ld -m elf_i386 lesson27.o -o lesson27
;**************************************************************
 
%include    'functions.asm'
 
SECTION .data
filename 	db 	'readme.txt', 		0x0    
contents  	db 	'-updated-', 		0x0   
 
SECTION .text
global  _start
 
_start:
 
    	mov	ecx, 		1              
    	mov     ebx, 		filename       
    	mov     eax, 		5              
    	int     0x80                 
 
    	mov     edx, 		2              
    	mov     ecx, 		0              
    	mov     ebx, 		eax            
    	mov     eax, 		19             
    	int     0x80                
 
   	mov     edx, 		9              
    	mov     ecx, 		contents       
    	mov     ebx, 		ebx            
    	mov     eax, 		4              
    	int     0x80                 
 
    	call    quit                
