void kernel_main () {
	unsigned char *vga_addr = (unsigned char*)0xB800;
	vga_addr[0] = 'Q';
	vga_addr[1] = 'W';
	vga_addr[2] = 'E';
	vga_addr[3] = 'R';
	vga_addr[4] = 'T';
	vga_addr[5] = 'Y';
	while(1);
}
