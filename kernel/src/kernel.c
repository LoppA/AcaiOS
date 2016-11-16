#include "stdio.h"
#include "registers.h"

void kernel_main () {

	clear_screen();

	printf ("\n\n\tBem vindo ao AcaiOS!!\n");
	printf ("\tO Sistema Operacional tao bom quanto Acai.\n");

	printf ("\n\nRegistradores: \n");

	printf ("\tcs: 0x%x\n\tds: 0x%x\n\tss: 0x%x\n", getCS(), getDS(), getSS());

	abort();
}
