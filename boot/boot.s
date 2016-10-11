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

	jmp 	start

start:
	# Resetar registradores
	xorw	%ax, 	%ax
	movw	%ax, 	%ds
	movw	%ax, 	%ss
	movw	%ax, 	%fs

	# Ler, fica no al	
	int	$0x16

	movb	$0x0A,		%ah
	movb	$0,		%bh
	movb	$0XAA,		%bl
	movw	$1,		%cx
	int	$0x10

	# if (al == '1') clear()
	cmp	$'1',		%al
	je	clear

	
jmp	start

clear:
	# Move cursor para inicio
	movb	$2,		%ah
	movb	$0,		%bh
	xorw	%dx,		%dx
	int	$0x10

loop_clear:

	# Coloca ' ' na tela e incrementa cursor
	movb	$0x0E,		%ah
	movb	$' ',		%al
	xorw	%bx,		%bx
	int	$0x10

	addw	$1,		%dx

	cmp	$2000,		%dx

	jl	loop_clear

	# Move cursor para inicio
	movb	$2,		%ah
	movb	$0,		%bh
	xorw	%dx,		%dx
	int	$0x10

jmp	start

. = _start + 510
.byte	0x55, 0xAA
