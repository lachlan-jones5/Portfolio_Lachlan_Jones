- This is my solution to the infamous FizzBuzz problem in both C++ and x86 Assembly.
- The C++ solution is straightfoward and was written just to compare the outputs I get from my Assembly program.

- To compile and link:

	FizzBuzz(C++):
		g++ FizzBuzz.cpp -o FizzBuzz
		
	FizzBuzz(x86 Assembly)
		nasm -f elf Main.asm
		ld -m elf_i386 Main.o -o FizzBuzz
