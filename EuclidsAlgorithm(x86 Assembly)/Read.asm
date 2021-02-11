; string readLine(variable, bytes)
; eax = variable
; ebx = bytes
readLine:

	push	edx
	push	ecx

	mov	edx, ebx
	mov	ecx, eax
	mov	ebx, 0
	mov	eax, 3	
	int	80h

	pop	ecx
	pop	edx

	ret

readInt:

	push	eax
	call	readLine

	pop	eax
	call	convertToInt
	ret

; This next function converts a string to an integer

convertToInt:

	push	ebx			; Preserve all registers
	push	ecx
	push	edx
	push	esi

	mov	esi, eax		; Move eax to esi

	xor	ecx, ecx		; Initialise the registers as 0
	xor	eax, eax

.loopMultiply:

	xor	ebx, ebx		; Set ebx to 0
	mov	bl, [esi + ecx]		; bl (8 bits) = lower of bx = lower of ebx
					; This iterates the bl pointer through the string
	cmp	bl, 48			; Check to make sure bl is an integer using ASCII
	jl	.done			; If it is not, finish the conversion
	cmp	bl, 57
	jg	.done

	sub	bl, 48			; Convert from ASCII character to an integer 
	add	eax, ebx		; Add the new integer we parsed to the total integer 

	mov	ebx, 10			; Move the place value to the correct spot  
	mul	ebx
	inc	ecx			; Increase ecx by 1

	jmp	.loopMultiply

.done:

	cmp	ecx, 0			; Check to see if anything was passed to this function (safety!)
	je	.popStack		; Restore everything if no integers were passed
	mov	ebx, 10			
	div	ebx			; Because in .loopMultiply, we actually multiplied by one too many in the final loop, so we're dividing down by 10 to make the integer correct	
	
.popStack:

	pop	esi
	pop	edx
	pop	ecx
	pop	ebx

	ret
