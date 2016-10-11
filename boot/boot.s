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

# char esta no al
putchar:
	movb	$0x0E,		%ah
	xorw	%bx,		%bx

	addw	$1,		%dx

	int	$0x10

	ret

# ecx: ponteiro para a string
print_str:

	print_loop:
		movb	(%ecx),	%al

		# if (al != '\0') 
		cmp	$0,		%al
		je	prologo_print

		call	putchar
		addl	$1,	%ecx

		jmp	print_loop

	prologo_print:

	ret

clear:
	# Move cursor para inicio
	xorw	%dx,		%dx
	call	move_cursor

	loop_clear:
		# Coloca ' ' na tela e incrementa cursor
		movb	$' ',		%al
		call	putchar

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

ram:
	int	$0x12
	movb	$'0',	%al
	call	putchar
	movb	$'x',	%al
	call	putchar
	movb	$' ',	%al
	call	putchar

	movl	$str_ram,	%ecx
	call	print_str

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


	# if (al == 4') reboot()
#	cmp	$'4',		%al
#	je	_reboot


	# if (al == '5') ram()
	cmp	$'5',		%al
	je	_ram

	
jmp	start

_clear:
	call	clear
	jmp	start

_reboot:
	call	clear
	call 	reboot
	jmp	start

_ram:
	call	clear
	call 	ram
	jmp	start

jmp	_start

str_ram:	.ascii	" KB of memory avaliable on RAM"

. = _start + 510
.byte	0x55, 0xAA
