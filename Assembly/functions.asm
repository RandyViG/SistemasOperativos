;**********************************************************
;	    Library for print strings and numbers
;**********************************************************

;----------------------------------------------------------
;	void	iprint( Integer number)
;	Integer	printing function (itoa)
;----------------------------------------------------------

iprint:
	push	eax
	push	ecx
	push	edx
	push	esi
	mov	ecx,		0

divideLoop:
	inc	ecx
	mov	edx,		0
	mov	esi,		10
	idiv	esi
	add	edx,		48
	push	edx
	cmp	eax,		0
	jnz	divideLoop

printLoop:
	dec	ecx
	mov	eax,		esp
	call	sprint
	pop	eax
	cmp	ecx,		0
	jnz	printLoop

	pop	esi
	pop	edx
	pop	ecx
	pop	eax
	ret
;---------------------------------------------------------------
;	void iprintLF (Integer number)	
;	Integer printing function with linefeed ( itoi )
;---------------------------------------------------------------

iprintLF:
	call	iprint
	push	eax
	mov	eax,		0x0A
	push	eax
	mov	eax,		esp
	call	sprint
	pop	eax
	pop	eax
	ret

;---------------------------------------------------------------
;	int slen( String message )
;	String length calculation function
;---------------------------------------------------------------

slen:
	push	ebx
	mov	ebx,		eax

nextchar:
	cmp	byte[eax],	0
	jz	finished
	inc	eax
	jmp	nextchar

finished:
	sub	eax,		ebx
	pop	ebx
	ret

;--------------------------------------------------------------
;	void sprint( String message )
;	String printing function
;--------------------------------------------------------------

sprint:
	push	edx
	push	ecx
	push	ebx
	push	eax
	call	slen

	mov	edx,		eax
	pop	eax
	
	mov	ecx,		eax
	mov	ebx,		1
	mov	eax,		4
	int	0x80

	pop	ebx
	pop	ecx
	pop	edx
	ret

;---------------------------------------------------------------
;	void sprintLF ( String message )
;	String printing with line feed dunctions
;---------------------------------------------------------------

sprintLF:
	call	sprint

	push	eax
	mov	eax,		0x0A
	push	eax
	mov	eax,		esp
	call	sprint
	pop	eax
	pop	eax
	ret

;---------------------------------------------------------------
;	void exit()
;	Exit program and restore resource
;---------------------------------------------------------------

quit:
	mov	ebx,		0
	mov	eax,		1
	int	0x80
	ret

;---------------------------------------------------------------
; 	int atoi (Integer number)
; 	Ascii to integer function (atoi)
;---------------------------------------------------------------

atoi:
	push	ebx
	push	ecx
	push	edx
	push	esi
	mov	esi,		eax
	mov	eax,		0
	mov	eax,		0

.multiplyLoop:
	xor	ebx,		ebx
	mov	bl,		[esi+ecx]
	cmp	bl,		48
	jl	.finished
	cmp	bl,		57
	jg	.finished

	sub	bl,		48
	add	eax,		ebx
	mov	ebx,		10
	mul	ebx
	inc	ecx
	jmp	.multiplyLoop

.finished:
	mov	ebx,		10
	div	ebx
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	ret
