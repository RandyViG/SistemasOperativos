;**************************************************************
;	   	   				Contar hasta 10
;	      Utilizando modulo para no salirse del rango
;Compilar:
;	nasm -f elf lesson10.asm
;	ld -m elf_i386 lesson11.o -o lesson11
;**************************************************************

%include	'functions.asm'

SECTION	.text
global	_start

_start:
	mov	ecx,		0

nextNumber:
	inc	ecx
	mov	eax,		ecx
	call	iprintLF
	cmp	ecx,		10
	jne	nextNumber

	call	quit
