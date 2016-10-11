.section	.text
.globl		_start

_start:
.code16
	# Move cursor para a linha 12, coluna 0
	movb	$0x0C,	%dh
	movb	$0,	%dl
	call	move_cursor

	jmp 	start

# Move cursor para as posicoes marcadas em dh, dl
move_cursor:
	movb	$2,	%ah
	movb	$0,	%bh
	int	$0x10

	ret

clear:
	# Move cursor para inicio
	xorw	%dx,		%dx
	call	move_cursor

loop_clear:

	# Coloca ' ' na tela e incrementa cursor
	movb	$0x0E,		%ah
	movb	$' ',		%al
	xorw	%bx,		%bx
	int	$0x10

	addw	$1,		%dx

	cmp	$2000,		%dx

	jl	loop_clear

	call	move_cursor

	# Move cursor para inicio
	xorw	%dx,		%dx
	call	move_cursor

	ret

reboot:
	int	$0x19
	ret

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
	je	_clear


	# if (al == 4') clear()
#	cmp	$'4',		%al
#	je	_reboot

	
jmp	start

_clear:
	call	clear
	jmp	start

_reboot:
	call	clear
	call 	reboot
	jmp	start

jmp	_start

. = _start + 510
.byte	0x55, 0xAA
