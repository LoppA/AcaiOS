.section	.text
.globl		_start

_start:
.code16
	# Move cursor para a linha 12, coluna 0
	movb	$2,	%ah
	movb	$0,	%bh
	movb	$0x0C,	%dh
	movb	$0,	%dl
	int	$0x10

	# Resetar registradores
	xorw	%ax, 	%ax
	movw	%ax, 	%ds
	movw	%ax, 	%ss
	movw	%ax, 	%fs

	jmp 	start

start:
	# Ler, fica no al	
	int	$0x16

	movb	$0x0A,		%ah
	movb	$0,		%bh
	movb	$0XAA,		%bl
	movw	$1,		%cx
	int	$0x10

	
jmp	_start

loop:	jmp	loop

. = _start + 510
.byte	0x55, 0xAA
