- This is a simple x86 assembly program that reads in two positive integers and finds the greatest common denominator of them
- To compile:

        nasm -f elf Main.asm
        ld -m elf_i386 Main.o -o EuclidsAlgorithm
        
- To run
       
        ./EuclidsAlgorithm
