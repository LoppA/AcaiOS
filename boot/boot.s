.section	.text
.globl		_start

_start:
.code16
	# Resetar registradores
	xorw	%ax, 	%ax
	movw	%ax, 	%ds
	movw	%ax, 	%ss
	movw	%ax, 	%fs
	jmp 	start

start:
	nop
loop:	jmp	loop

. = _start + 510
.byte	0x55, 0xAA
