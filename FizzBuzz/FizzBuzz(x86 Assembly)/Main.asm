%include 'Quit.asm'
%include 'Print.asm'

segment .data

	fizzN	equ	3		; Using these fizzNbuzz variables, if we want the two numbers to be different, we only have to change what these variables are equal to here.
	buzzN	equ	5
	fizz	db	'Fizz', 0h	; This is the "Fizz" string	
	buzz	db	'Buzz', 0h	; This is the 'Buzz" string
	newL	db	0ah

segment .text

	global _start

_start:

	xor	ecx, ecx		; Set ecx equal to 0 (ecx will be our counter variable)

startCount:

	xor	esi, esi		; esi will be 0 if either 'fizz' or 'buzz' was printed, but will be greater than 0 otherwise
	inc	ecx

fizzFunc:

	mov	eax, ecx		; Move ecx into eax so we can divide eax by fizzN
	mov	ebx, fizzN
	xor	edx, edx		; Clear remainder register
	idiv	ebx			; Divide eax by ebx
	cmp	edx, 0			; Check to see if remainder is 0
	jnz	buzzFunc		; If it is not, skip to buzzFunc

	inc	esi			; If it is, increment esi for later use and print 'Fizz'
	mov	eax, fizz
	call	print

buzzFunc:

	mov	eax, ecx		; Same process applies for buzzFunc as it does fizzFunc
	mov	ebx, buzzN
	xor	edx, edx
	idiv	ebx
	cmp	edx, 0
	jnz	number

	inc	esi
	mov	eax, buzz
	call	print

number:

	cmp	esi, 0			; If esi != 0, then fizz or buzz has been printed, and we don't need to print the number
	jnz	final			; Otherwise, we do need to print the number

	mov	eax, ecx
	call	iprint

final:

	mov	eax, newL		; Print a new line
	call	print

	cmp	ecx, 100		; Loop if less than 100
	jl	startCount

	call	quit			; Call quit function

	
