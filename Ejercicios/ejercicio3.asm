
%include		'functions.asm'

SECTION .data
mult	db	' * ',	0x0
equal	db	' = ',	0x0	

SECTION	.text
global	_start

_start:
	mov	eax,		0
	mov	ebx,		0
	inc 	ebx

tables:
	cmp	eax,		10
	jz	exit
	inc	eax
	push	eax
	push	ebx
	call	multiply
	pop	ebx
	pop	eax
	jmp	tables	

multiply:
	push	ebx
	push	eax
	call	iprint		   	;Imprime el numero de la tabla
	mov	eax,		mult
	call	sprint		    	;Imprime el simbolo '*'
	mov	eax,		ebx
	call	iprint		    	;Imprime el multiplicador
	mov	eax,		equal
	call	sprint		    	;Imprime el simbolo '='
	pop	eax
	pop	ebx
	push	eax
	mul	ebx
	call	iprintLF	    	;Imprime el producto
	pop	eax

	cmp	ebx,		10
	jz	endTable
	inc 	ebx
	jmp 	multiply

endTable:
	ret

exit:
	call	quit
