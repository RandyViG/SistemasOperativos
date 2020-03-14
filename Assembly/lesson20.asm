;****************************************************************
;			  Process Forking
;Compilar:
;	nasm -f elf lesson20.asm
;	ld -m elf_1386 lesson20.o -o l20
;****************************************************************

%include	'functions.asm'

SECTION	.data
childMsg	db	'This is the child process',	0x0
parentMsg	db	'This is the parent process',	0x0

SECTION	.text
global	_start

_start:
	mov	eax,		2
	int	0x80

	cmp	eax,		0
	jz	child

parent:
	mov	eax,		parentMsg
	call	sprintLF
	
	call	quit

child:
	mov	eax,		childMsg
	call	sprintLF
	
	call	quit
