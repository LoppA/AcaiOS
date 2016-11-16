#include "vga.h"

void kernel_main () {
	int foo = 11;

	printf ("Inteiro: \t%d\n", foo);
	printf ("Binario: \t%b\n", foo);
//	printf ("Hexadecimal: \t%x\n", foo);

	abort ();
}
