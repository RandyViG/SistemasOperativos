;**************************************************************
;	   	    Hello world en Ensamblador
;Compilar:
;	nasm -f elf lesson1.asm
;	ld -m elf_i386 lesson1.o -o lesson1
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

