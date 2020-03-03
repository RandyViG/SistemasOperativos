;**************************************************************
;	   	      Modularizando código
;	      Definiendo funciones en otro archivo
;Compilar:
;	nasm -f elf lesson5.asm
;	ld -m elf_i386 lesson5.o -o lesson5
;**************************************************************

%include	'functions.asm'

SECTION	.data
msg1	db	'Hello, brave new wold!',	0x0A
msg2	db	'This is how we recycle in NASM',	0x0A

SECTION	.text
global _start

_start:
	mov	eax,	msg1
	call	sprint

	mov	eax,	msg2
	call	sprint

	call quit
