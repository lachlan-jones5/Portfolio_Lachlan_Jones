printInt:

	push	eax 			; Push to stack to preserve values
	push	ecx			
	push	edx
	push	esi

	xor	ecx, ecx		; Set ecx equal to zero

divideLoop:				; Beginning of loop

	inc	ecx			; Increment ecx by 1			
	xor	edx, edx		; Set edx = 0
	mov	esi, 10			; Move the variable 10 into the esi register
	idiv	esi			; Divide eax by esi (eax division implied w/ idiv)
	add	edx, 48			; Add 48 to edx to convert to ASCII value integer (value in here is the remainder of previous division ie. the last digit in the integer)
	push	edx			; Push the string-ready value onto the stack
	cmp	eax, 0			; Compare eax to 0
	jnz	divideLoop		; If eax is not zero (null byte), return to divideLoop label

printLoop:

	dec	ecx			; Decrease ecx by 1 
	mov	eax, esp		; Point eax to the same location as esp
	call	print			; Print the digit
	pop	eax			; Get the next digit off of the stack 
	cmp	ecx, 0			; Check to see if we have printed everything
	jnz	printLoop		; If not, repeat

	pop	esi			; Get back all values that were preserved
	pop	edx
	pop	ecx
	pop	eax
	ret

; -----------------------------------

printIntln:

	call	printInt		; Calls the above section

	push	eax			; Preserve eax
	mov	eax, 0ah		; Put linefeed character into eax
	push	eax			; Put eax onto stack
	mov	eax, esp		; print function requires a pointer, so give it one!
	call	print			; Print the linefeed
	pop	eax
	pop	eax

	ret

; -----------------------------------
stringLengthCalculator:

	push	ebx
	mov	ebx, eax

getNextChar:

	cmp	byte [eax], 0
	jz	finalised
	inc	eax
	jmp	getNextChar

finalised:

	sub	eax, ebx
	pop	ebx
	ret
	
; -----------------------------------
print:

	push	edx
	push	ecx
	push	ebx
	push	eax
	call	stringLengthCalculator

	mov	edx, eax
	pop	eax

	mov	ecx, eax
	mov	ebx, 1
	mov	eax, 4
	int	80h
	
	mov	eax, ecx
	pop	ebx
	pop	ecx
	pop	edx
	ret

; -------------------------------------

println:

	call	print

	push	eax
	mov	eax, 0ah
	push	eax
	mov	eax, esp
	call	print
	pop	eax
	pop	eax
	ret
