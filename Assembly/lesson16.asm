;**************************************************************
;	   	    		Calculator (atoi)
;Compilar:
;	nasm -f elf lesson16.asm
;	ld -m elf_i386 lesson16.o -o lesson16
;**************************************************************
%include	'functions.asm'

SECTION	.text
global	_start

_start:
	pop	ecx
	pop	edx
	sub	ecx,		1
	mov	edx,		0

nextArg:
	cmp	ecx,		0x0
	jz	noMoreArgs
	pop	eax
	call	atoi
	add	edx,		eax
	dec	ecx
	jmp	nextArg

noMoreArgs:
	mov	eax,		edx
	call	iprintLF
	call	quit
