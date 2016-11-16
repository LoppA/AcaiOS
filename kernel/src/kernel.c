#include "stdio.h"

void kernel_main () {
	int foo = 10, bar = 1337;

	clear_screen();

	printf ("Inteiro: \t%d\n", foo);
	printf ("Binario: \t%b\n", foo);
	printf ("Hexadecimal: \t%x\n\n", foo);

	printf ("Inteiro: \t%d\nBinario: \t%b\nHexadecimal: \t%x\n\n", bar, bar, bar);

	abort();
}
