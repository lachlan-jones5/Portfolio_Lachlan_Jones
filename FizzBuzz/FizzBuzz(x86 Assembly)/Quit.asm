; This function quits the program safely
quit:

	mov	ebx, 0		; This is 'return 0' in C - return no errors.
	mov	eax, 1		; This is the system call number for SYS_EXIT
	int	80h		; Calling the 'system call' interrupt
