;**************************************************************
;			Telling the time
;Compilar:
;	nasm -f elf lesson21.asm
;	ld -m elf_i386 lesson21.o l21
;**************************************************************

%include	'functions.asm'

SECTION	.data
msg	db	'Seconds since jan 01 1970: ',		0x0

SECTION	.text
global	_start

_start:

	mov	eax,		msg
	call	sprint

	mov	eax,		13
	int	0x80

	call	iprintLF
	call	quit
