;**************************************************************
;	   	   					User Input
;	      
;Compilar:
;	nasm -f elf lesson9.asm
;	ld -m elf_i386 lesson9.o -o lesson9
;**************************************************************

%include	'functions.asm'

SECTION	.data
msg1	db	'Please enter yout name: ',	0x0
msg2	db	'hello, ',			0x0

SECTION	.bss
sinput:	resb	255

SECTION	.text
global	_start

_start:
	mov	eax,		msg1
	call	sprint
	
	mov	edx,		255
	mov	ecx,		sinput
	mov	ebx,		0
	mov	eax,		3
	int	0x80

	mov	eax,		msg2
	call	sprint
	mov	eax,		sinput
	call	sprint

	call	quit
