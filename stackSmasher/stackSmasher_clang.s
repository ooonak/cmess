	.text
	.file	"stackSmasher.c"
	.globl	cpyPrint
	.align	16, 0x90
	.type	cpyPrint,@function
cpyPrint:                               # @cpyPrint
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movabsq	$.L.str, %rax
	leaq	-12(%rbp), %rcx
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rsi
	movq	%rcx, %rdi
	movq	%rcx, -24(%rbp)         # 8-byte Spill
	movq	%rax, -32(%rbp)         # 8-byte Spill
	callq	strcpy
	movq	-32(%rbp), %rdi         # 8-byte Reload
	movq	-24(%rbp), %rsi         # 8-byte Reload
	movq	%rax, -40(%rbp)         # 8-byte Spill
	movb	$0, %al
	callq	printf
	movl	%eax, -44(%rbp)         # 4-byte Spill
	addq	$48, %rsp
	popq	%rbp
	retq
.Ltmp3:
	.size	cpyPrint, .Ltmp3-cpyPrint
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp4:
	.cfi_def_cfa_offset 16
.Ltmp5:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp6:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	-32(%rbp), %rdi
	movl	$0, -4(%rbp)
	movq	.Lmain.string, %rax
	movq	%rax, -32(%rbp)
	movq	.Lmain.string+8, %rax
	movq	%rax, -24(%rbp)
	movw	.Lmain.string+16, %cx
	movw	%cx, -16(%rbp)
	callq	cpyPrint
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
.Ltmp7:
	.size	main, .Ltmp7-main
	.cfi_endproc

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%s\n"
	.size	.L.str, 4

	.type	.Lmain.string,@object   # @main.string
	.section	.rodata.str1.16,"aMS",@progbits,1
	.align	16
.Lmain.string:
	.asciz	"Longer than three"
	.size	.Lmain.string, 18


	.ident	"clang version 3.6.1 (tags/RELEASE_361/final)"
	.section	".note.GNU-stack","",@progbits
