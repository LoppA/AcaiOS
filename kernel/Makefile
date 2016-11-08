# Made by Iron & VVillam

# NUNCA EXECUTAR COMANDO DE PEN DRIVE VIA MAKEFILE!!!!!!
# Bootable pen drive: dd if=boot.bin of=/dev/fd0 count=1 bs=512
# Edited by Bebe

KERNELNAME=AcaiOS\ -\ GRUB\ Version\ 0.0.1 

# Directories
BLDDIR=build
INCDIR=include
SRCDIR=src
OBJDIR=$(SRCDIR)/obj

# Search for files
SRC=$(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/arch/*.c)
ASMSRC=$(wildcard $(SRCDIR)/*.s) $(wildcard $(SRCDIR)/arch/*.s)
DEPS=$(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/arch/*.h)

# Generate .o object files rules
OBJ=$(foreach file, $(SRC), $(file:$(SRCDIR)/%.c=$(OBJDIR)/%.o))
ASMOBJ=$(foreach file, $(ASMSRC), $(file:$(SRCDIR)/%.s=$(OBJDIR)/%.o))

LINKERSCRIPT=linker.ld

CC=gcc
CFLAGS=-fno-stack-protector -fno-builtin -ffreestanding -nostdinc -I./$(INCDIR) -m32
ASSEMBLER=as
ASMFLAGS=--32



# Compile .c files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@echo Building $*
	@$(CC) -c -o $(subst arch/,, $@) $< $(CFLAGS)

#Assemble .s files
$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@echo Assembling $*
	@$(ASSEMBLER) $< $(ASMFLAGS) -o $@

#Link files into executable
main: $(OBJ) $(ASMOBJ)
	@echo Linking object files to executable
	@ld -T $(LINKERSCRIPT) -m elf_i386 $(subst arch/,, $(OBJ)) $(ASMOBJ) -o $(BLDDIR)/$(KERNELNAME)



# Utility directives
clean:
	@touch $(BLDDIR)/temp
	@touch $(OBJDIR)/temp
	rm $(BLDDIR)/*
	rm $(OBJDIR)/*

# Run directives
run:
	qemu-system-i386 --kernel $(BLDDIR)/$(KERNELNAME)

runv:
	qemu-system-x86_64 --kernel $(BLDDIR)/$(KERNELNAME)
