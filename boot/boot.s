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
	# Ler, fica no al	
	int	$0x16
	
	# Imprimir na primeira posicao da tela
	movb	$0x1E, 		%ah
	movl	$0xB8000,	%ecx
	movw	%ax, 		(%ecx)

	# if (al == '1') clear()
	cmp	$'1',		%al
	je	clear
	
jmp	_start

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

jmp	_start

loop:	jmp	loop

. = _start + 510
.byte	0x55, 0xAA
