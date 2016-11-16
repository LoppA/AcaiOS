#include "vga.h"

void kernel_main () {
	int foo = 10;

	clear_screen();

	printf ("Inteiro: \t%d\n", foo);
	printf ("Binario: \t%b\n", foo);

	abort();
}
