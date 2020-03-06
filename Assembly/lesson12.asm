;**************************************************************
;	   	   			Calculadora - Suma
;	      
;Compilar:
;	nasm -f elf lesson12.asm
;	ld -m elf_i386 lesson12.o -o lesson12
;**************************************************************

%include	'functions.asm'

SECTION	.text
global	_start

_start:
	mov	eax,		90
	mov	ebx,		9
	add	eax,		ebx
	call	iprintLF

	call	quit
