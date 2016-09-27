.section	.text
.globl		_start

_start:
.code16
	xorw	%ax, %ax
	movw	%ax, %ds
	movw	%ax, %ss
	movw	%ax, %fs
	jmp 	start

start:
loop:
	#Ler, fica no al	
	xorw	%ax, %ax
	int	$0x16
	
	movb	$0x1E, %ah
	movl	$0xB8000, %ecx
	movw	%ax, (%ecx)
	
 jmp	loop

 clear:


 jmp	loop

. = _start + 510
.byte	0x55, 0xAA
