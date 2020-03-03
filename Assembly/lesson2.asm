
;**************************************************************
;	   	    Hello world en Ensamblador
;	      Corrigiendo error, agregando return code 
;Compilar:
;	nasm -f elf lesson2.asm
;	ld -m elf_i386 lesson2.o -o lesson2
;**************************************************************
SECTION	.data
msg	db	'Hello World!',	0x0A

SECTION	.text
global	_start

_start:
	
	mov	edx,	13
	mov	ecx,	msg
	mov	ebx,	1
	mov	eax,	4
	int	0x80

	mov	ebx,	0
	mov	eax,	1
	int	0x80

