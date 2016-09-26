.section	.data
op:	.ascii	"1"

.section	.text
.globl		_start
#.code16

_start:	
loop:
	# Ler
	movl	$3,	%eax
	movl	$1,	%ebx
	movl	$op,	%ecx
	movl	$1,	%edx
	int	$0x80
	
	# Imprimir
	movl	$4,	%eax
	movl	$2,	%ebx
	movl	$op,	%ecx
	movl	$1,	%edx
	int	$0x80

	jmp 	loop

#. = _start + 510
#.byte		0x55, 0xAA
