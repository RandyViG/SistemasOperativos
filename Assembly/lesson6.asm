;**************************************************************
;	   	   Terminando bytes con Null
;	      
;Compilar:
;	nasm -f elf lesson6.asm
;	ld -m elf_i386 lesson6.o -o lesson6
;**************************************************************

%include	'functions.asm'

SECTION .data
msg1	db	'Hello, brave new world!',	0x0A,	0x0
msg2	db	'This is how we recycle in NASM.',	0x0A,	0x0

SECTION	.text
global	_start

_start:
	mov	eax,	msg1
	call	sprint
	mov	eax,	msg2
	call	sprint

	call	quit
