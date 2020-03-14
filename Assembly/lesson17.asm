;**************************************************************
;			    Namespace
;Compilar:
;	nasm -f elf lesson17.asm
;	ld -m elf_i386 lesson17.o -o l17
;**************************************************************

%include	'functions.asm'

SECTION	.data
msg1	db	'Jumping to finished label.',		0x0
msg2	db	'Inside subroutinr number: ',		0x0
msg3	db	'Inside subroutine "finished".', 	0x0

SECTION	.text
global	_start

_start:
	
subrountineOne:
	mov	eax,		msg1
	call	sprintLF
	jmp	.finished

.finished:
	mov	eax,		msg2
	call	sprint
	mov	eax,		1
	call	iprintLF

subroutineTwo:
	mov	eax,		msg1
	call	sprintLF
	jmp	.finished

.finished:
	mov	eax,		msg2
	call	sprint
	mov	eax,		2
	call	iprintLF

	mov	eax,		msg1
	call	sprintLF
	jmp	.finished

.finished:
	mov	eax,		msg3
	call	sprintLF
	call	quit
