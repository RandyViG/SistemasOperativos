;**************************************************************
;	   	   				Paso de argumentos
;	      
;Compilar:
;	nasm -f elf lesson6.asm
;	ld -m elf_i386 lesson6.o -o lesson6
;**************************************************************

%include	'functions.asm'

SECTION	.data
global	_start

_start:
	pop	ecx

nextArg:
	cmp	ecx,	0x0
	jz	noMoreArgs
	pop	eax
	call	sprintLF
	dec	ecx
	jmp	nextArg

noMoreArgs:
	call	quit
