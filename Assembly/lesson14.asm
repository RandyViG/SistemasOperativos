;**************************************************************
;	   	    		Calculator Multiplication
;Compilar:
;	nasm -f elf lesson14.asm
;	ld -m elf_i386 lesson14.o -o lesson14
;**************************************************************
%include		'functions.asm'

SECTION	.data
global	_start

_start:
	mov	eax,		90
	mov	ebx,		9
	mul	ebx
	call	iprintLF

	call	quit
