; This is the main Euclid's algorithm function
; eax = variable1
; ebx = variable2

euclidsAlgorithm:

	push	ecx			; Preserve registers
	push	edx

	cmp	eax, 0			; If one or more of the integers is 0, we skip code to protect against any attempts to divide by 0
	jz	.done
	cmp	ebx, 0
	jz	.zeros
	
	cmp	eax, ebx
	jg	.mainAlgorithm		; Compare the integers, switch them if bigger
					; Taken from Euclid's Algorithm as defined in The Art of Computer Programming by Donald Knuth
	
	mov	ecx, eax
	mov	eax, ebx
	mov	ebx, ecx
					; ecx == ebx
					; eax
					
.mainAlgorithm:

	xor	edx, edx		; Ensures remainder register is empty
	div	ebx			; Divide eax by ebx (eax is implied)
	cmp	edx, 0			; Check to see if the reminder is 0
	jz	.done			; If it is, we have found the GCD in ebx
	
	mov	eax, ebx		; Move ebx into eax and the remainder into ebx so we can find GCD of next step
	mov	ebx, edx
	
	jmp	.mainAlgorithm		; Loop algorithm
					
.done:
	
	mov	eax, ebx		; Move the GCD into eax for easy access in next functions
	pop	edx			; Revive registers
	pop	ecx			 

	ret

.zeros:

	mov	ebx, eax
	jmp	.done

	

	
	
