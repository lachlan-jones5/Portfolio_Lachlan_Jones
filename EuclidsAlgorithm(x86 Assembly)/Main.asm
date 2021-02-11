; GCD(x, y) = GCD(x mod y, y)

%include	'Print.asm'
%include	'Quit.asm'
%include	'Read.asm'
%include	'EuclidsAlgorithm.asm'

segment .data

	output1	db	'First number: ', 0h
	output2	db	'Second number: ', 0h
	breakL	db	'---------------------------------', 0h
	hello	db	'Please enter an integer between 0 and 2147483647', 0h
	finalMessage	db	'GCD = ', 0h
	bufferS	equ	11

segment .bss

	input1:	resd	bufferS		
	input2:	resd	bufferS		

segment .text

	global _start

_start:
	
	mov	eax, hello
	call	println			; Print instructionary message

	mov	eax, output1
	call	print			; Prompt for first integer input

	mov	ebx, bufferS		; Size of string to be read in
	mov	eax, input1		; Variable to put input into
	call	readLine		; Call readline function

	mov	eax, output2		; Prompt for second integer
	call	print

	mov	ebx, bufferS		; Read second integer
	mov	eax, input2
	call	readLine

	mov	eax, breakL		; Print a <hr /> thing
	call	println

	mov	eax, input2		; Convert the inputs into integers
	call	convertToInt
	mov	ebx, eax
	mov	eax, input1
	call	convertToInt

	call 	euclidsAlgorithm    	; Call the main algorithm
	
	push	eax			; Display final message and output result
	mov	eax, finalMessage
	call	print
	pop	eax
	call	printIntln

	call	quit
