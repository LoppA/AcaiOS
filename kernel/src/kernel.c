void kernel_main () {
	unsigned char *vga_addr = (unsigned char*)0xB8000;
	vga_addr[0] = 'Q';
	vga_addr[1] = 0x0F;
	vga_addr[2] = 'W';
	vga_addr[3] = 0x0F;
	vga_addr[4] = 'E';
	vga_addr[5] = 0x0F;
	vga_addr[6] = 'R';
	vga_addr[7] = 0x0F;
	vga_addr[8] = 'T';
	vga_addr[9] = 0x0F;
	vga_addr[10] = 'Y';
	vga_addr[11] = 0x0F;
	while(1);
}
