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

#mudei aqui
#imprime dispositivos conectados
conectados:
	#chama a syscall que coloca as informacoes no ax
	int $0x11
	
	#imprimo a string e verifica se tem o dispositivo conectado
	movl	$str_game_adapter,	%ecx
	call	print_str
	
	movw	%ax,	%bx	
	movw	$0b0010000000000000,		%cx
	andw	%cx,	%bx
	cmp		%cx,	%bx
	je		game_S
	jmp		game_N
	
	#caso tenha ele imprime S, caso n tenha ele imprime N
	game_S:
		movb	$'S',	%al
		jmp game_print
		
	game_N:
		movb	$'N',	%al
	
	game_print:
		call	putchar
		
	#funcao que move o cursor para a proxima linha
	movb	$0x01,	%dh
	movb	$0x00,	%dl
	call	move_cursor
	
	
	
	movl	$str_internal_modem,	%ecx
	call	print_str
	movw	%ax,	%bx	
	movw	$0b0100000000000000,		%cx
	andw	%cx,	%bx
	cmp		%cx,	%bx
	je		modem_S
	jmp		modem_N
	
	modem_S:
		movb	$'S',	%al
		jmp modem_print
		
	modem_N:
		movb	$'N',	%al
	
	modem_print:
		call	putchar
		
		
	movb	$0x02,	%dh
	movb	$0x00,	%dl
	call	move_cursor
	
	movl	$str_printer_ports,	%ecx
	call	print_str
	movw	%ax,	%bx	
	movw	$0b1000000000000000,		%cx
	andw	%cx,	%bx
	cmp		%cx,	%bx
	je		printer_S
	jmp		printer_N
	
	printer_S:
		movb	$'S',	%al
		jmp printer_print
		
	printer_N:
		movb	$'N',	%al
	
	printer_print:
		call	putchar
	
	movb	$0x04,	%dh
	movb	$0x00,	%dl
	call	move_cursor
	
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

	#mudei aqui
	# if (al == '3') conectados()
	cmp	$'3',		%al
	je	_conectados

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

#mudei aqui	
_conectados:
	call clear
	call conectados
	jmp start

_ram:
	call	clear
	call 	ram
	jmp	start

jmp	_start

str_ram:	.ascii	" KB of memory avaliable on RAM\0"

#mudei aqui
str_game_adapter:	.ascii	" Game adapter: \0"
str_internal_modem:	.ascii	" Internal modem: \0"
str_printer_ports:	.ascii	" Printer ports: \0"

. = _start + 510
.byte	0x55, 0xAA