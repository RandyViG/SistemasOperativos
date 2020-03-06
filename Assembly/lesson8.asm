
%include	'functionsL7.asm'

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
