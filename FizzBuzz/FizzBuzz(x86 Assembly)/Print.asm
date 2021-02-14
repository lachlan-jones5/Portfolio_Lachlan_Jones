; This function calculates the length of the string given to it
stringLengthCalculator:
	
	push	ebx		; Preserve ebx because we want to use it
	mov	ebx, eax	; Move the string into ebx because we are going to increment eax and then finally use pointer arithmetic to figure out how long the string is

getNextChar:

	cmp	byte [eax], 0	; Check to see if we have reached the null terminator byte
	jz	finished	; If we have reached the null terminator byte, then jump to the finished function
	inc	eax		; If we haven't then increment the eax pointer to point to the next character
	jmp	getNextChar	; Continue loop

finished:

	sub	eax, ebx	; Do the pointer arithmetic to figure out how long the string is
	pop	ebx		; Restore the register
	ret			; Return control to the parent function


; _______________________________________________________________________________________________________

; This is the print function.  It will make use of the stringLengthCalculator function to print the incoming strings

print:

	push	edx		; Preserve registers
	push	ecx
	push	ebx
	push	eax		; Preserve this register containing the string, because when we call the stringLengthCalculator function, the result is returned in eax 
	call	stringLengthCalculator
	
	mov	edx, eax	; Now we have the string length, and we move it from eax into edx (as edx is where string lengths are stored to print to standard out
	pop	ecx		; Bring the string back from the stack

	; WARNING!!!!!!!! : WE may need to pop into eax and then move eax -> ecx if there is an issue

	mov	ebx, 1		; Write to standard out file
	mov	eax, 4		; SYS_WRITE system call code
	int	80h		

	mov	eax, ecx	; Move the string back into eax just in case it is still needed later
	pop	ebx		; Restore registers
	pop	ecx
	pop	edx
	ret

; _________________________________________________________________________________________________________

; This next function is the println function, equivalent to the println function in Java.  It will make use of the print function but also print a linefeed at the end

println:

	call	print		; Print the string

	push	eax		; Preserve the eax string
	mov	eax, 0ah	; Move the linefeed character into eax

	push	eax		; SYS_WRITE expects us to pass a pointer address, not the ASCII character itself.  So, we push eax onto the stack and then get the address of the character by moving esp into eax.

	mov	eax, esp

	call	print		; Prints the linefeed

	pop	eax		; Pop off linefeed
	pop	eax		; Pop off the eax string 

	ret

; __________________________________________________________________________________________________________

; This function is used to print integers, as integers have to be converted to ASCII before being output

iprint:

	push	eax		; Preserve the registers
	push	esi
	push	ecx
	push	edx

	xor	ecx, ecx	; Zero the ecx register

divideLoop:			; This function divides the integer down, converts it to an ASCII character and then adds it to the stack to be printed in the following function

	inc	ecx		
	xor	edx, edx	; Ensure that the division register is empty
	mov	esi, 10
	idiv	esi		; Divide eax by esi (eax has the integer we want to print in it 
	add	edx, 48		; Adding 48 to the integer converts it to the correct ASCII value
	push	edx		; Push the value onto the stack to be printed later
	cmp	eax, 0	
	jnz	divideLoop	; Loop if we have not yet hit a null byte

printLoop:			; The string was constructed in the above function, now we will print it in this function

	dec	ecx		; Decrease ecx by 1
	mov	eax, esp	; Point these two registers to the same place, as SYS_WRITE needs a pointer.  So prior to popping eax, we need to point eax at esp, print what's there, and then pop eax to access the next integer.
	call	print		; Print the digit
	pop	eax		; Pop off the digit so we can access the next one in the next loop
	cmp	ecx, 0
	jnz	printLoop	; If we hit the terminating byte, we have finished printing the integer.  If not. loop

	pop	edx		; Restore all values
	pop	ecx
	pop	esi
	pop	eax
	ret

; This function will call the iprint function and then print a linefeed character

iprintln:

	call	iprint

	push	eax		; Preserve eax because we want to use it
	mov	eax, 0ah	; Move linefeed character into eax
	push	eax		; Push eax onto stack because SYS_WRITE expects a pointer, not an ASCII character
	mov	eax, esp
	call	print		; Print the linefeed
	
	pop	eax		; Get linefeed
	pop	eax		; Restore eax

	ret
