CFLAGS= -ffreestanding -nostdinc -I./include -m32

all:
	as --32 $(file).s -o "$(file)".o
	ld -m elf_i386 -nostdlib -N -Ttext 7C00 "$(file)".o -o "$(file)".elf
	objcopy -O binary "$(file)".elf "$(file)".bin
	qemu-system-i386 "$(file)".bin -boot a

clean:
	rm ./*.bin ./*.o ./*.elf

assembly:
	as --32 "$(file)".s -o "$(file)".o
#	ld -m elf_i386 "$(file)".o -o "$(file)"

c:
	gcc -c $(file).c -o $(file).o $(CFLAGS)
