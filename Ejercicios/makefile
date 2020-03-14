run:	ejercicio2.o
	ld -m elf_i386	ejercicio2.o -o e2

ejercicio2.o:	ejercicio2.asm functions.asm
		nasm -f elf ejercicio2.asm

clean:	
	rm -f *.o e2
