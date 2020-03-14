;***************************************************************
;			  Execute Command
;Compilar:
;	nasm -f elf lesson19.asm
;	ld -m elf_i386 lesson19.o -o l19
;***************************************************************

%include	'functions.asm'

SECTION	.data
command		db	'/bin/echo',		0x0
arg1		db	'Hello World!',		0x0
arguments	dd	command
		dd	arg1
		dd	0x0
environment	dd	0x0

SECTION	.text
global	_start

_start:

	mov	edx,		environment
	mov	ecx,		arguments
	mov	ebx,		command
	mov	eax,		11
	int	0x80
	
	call	quit
