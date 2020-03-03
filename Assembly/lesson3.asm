
;**************************************************************
;	   	   Manejo de Cadenas Dinamicas
;			Calculando tamaño
;Compilar:
;	nasm -f elf lesson3.asm
;	ld -m elf_i386 lesson3.o -o lesson3
;**************************************************************

SECTION	.data
msg	db	'Hello, brave new world!',	0x0A

SECTION .text
global	_start

_start:
	mov 	ebx,	msg
	mov	eax,	ebx

nextchar:
	cmp	byte[eax],	0	;byte[] toma lo que esta en eax por byte 
	jz	finished		;i el resultado de cmp es != 0 salta la instruccion inmediata, de lo contario hace el salto a la rutina finished
	inc	eax
	jmp	nextchar

finished:
	sub	eax,	ebx		;SUB siempre necesita el registro eax, ahi es donde guarda el resultado

	mov	edx,	eax
	mov	ecx,	msg
	mov	ebx,	1
	mov	eax,	4
	int	0x80
	
	mov	ebx,	0
	mov	eax,	1
	int	0x80
	
