	.file	"hash.c"
	.text
	.comm	head,8,8
	.globl	StrTmp
	.bss
	.align 32
	.type	StrTmp, @object
	.size	StrTmp, 80
StrTmp:
	.zero	80
	.text
	.globl	InitHashmap
	.type	InitHashmap, @function
InitHashmap:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
	movl	$400, -12(%rbp)
	movl	$80, %edx
	movl	$0, %esi
	leaq	StrTmp(%rip), %rdi
	call	memset@PLT
	movl	$0, -16(%rbp)
	jmp	.L2
.L3:
	movq	head(%rip), %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	$0, 80(%rax)
	movq	head(%rip), %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movl	$80, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movq	head(%rip), %rcx
	movl	-16(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movq	$0, 88(%rax)
	addl	$1, -16(%rbp)
.L2:
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jl	.L3
	movq	-8(%rbp), %rax
	movq	%rax, head(%rip)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	InitHashmap, .-InitHashmap
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"malltest.txt"
.LC2:
	.string	"%s"
	.text
	.globl	fwriteHash
	.type	fwriteHash, @function
fwriteHash:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -12(%rbp)
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	jmp	.L5
.L8:
	movl	$80, %edx
	movl	$0, %esi
	leaq	StrTmp(%rip), %rdi
	call	memset@PLT
	movq	-8(%rbp), %rax
	leaq	StrTmp(%rip), %rdx
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_fscanf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	jne	.L9
	leaq	StrTmp(%rip), %rdi
	call	Hash
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	PutHashmap
	movl	$80, %edx
	movl	$0, %esi
	leaq	StrTmp(%rip), %rdi
	call	memset@PLT
.L5:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L8
	jmp	.L7
.L9:
	nop
.L7:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fwriteHash, .-fwriteHash
	.section	.rodata
.LC3:
	.string	"\n%d\n"
	.align 8
.LC4:
	.string	"\351\230\205\350\257\273\347\254\254%d\344\270\252\350\212\202\347\202\271\347\232\204\345\206\205\345\256\271\344\270\272%s  \350\212\202\347\202\271\351\225\277\345\272\246\344\270\272%d  \345\234\260\345\235\200\344\270\272 %p,next\345\234\260\345\235\200\344\270\272%p\n"
	.align 8
.LC5:
	.string	"\351\230\205\350\257\273\347\254\254%d\344\270\252\350\212\202\347\202\271\347\232\204\345\206\205\345\256\271\344\270\272%s  \346\240\207\350\257\206\344\270\272%d  \345\234\260\345\235\200\344\270\272 %p,next\345\234\260\345\235\200\344\270\272%p\n"
	.align 8
.LC6:
	.string	"\n\n\346\200\273\345\205\261\346\234\211\350\277\231\344\271\210\345\244\232\344\270\252\350\266\205\350\277\207\357\274\221\357\274\232%d\n"
	.text
	.globl	readnode
	.type	readnode, @function
readnode:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	head(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	$400, -20(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L11
.L16:
	movq	head(%rip), %rax
	movl	80(%rax), %eax
	testl	%eax, %eax
	je	.L12
	movq	head(%rip), %rax
	movl	80(%rax), %eax
	cmpl	$1, %eax
	jle	.L13
	movq	head(%rip), %rax
	movl	80(%rax), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -28(%rbp)
.L13:
	movq	head(%rip), %rax
	movq	%rax, -16(%rbp)
	jmp	.L14
.L15:
	movq	-16(%rbp), %rax
	movq	88(%rax), %rdi
	movq	-16(%rbp), %rax
	movl	80(%rax), %ecx
	movq	-16(%rbp), %rdx
	movq	-16(%rbp), %rsi
	movl	-24(%rbp), %eax
	movq	%rdi, %r9
	movq	%rsi, %r8
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movq	88(%rax), %rax
	movq	%rax, -16(%rbp)
.L14:
	cmpq	$0, -16(%rbp)
	jne	.L15
.L12:
	movq	head(%rip), %rax
	movq	88(%rax), %rsi
	movq	head(%rip), %rcx
	movq	head(%rip), %rax
	movl	80(%rax), %edx
	movq	head(%rip), %rax
	movq	%rax, %rdi
	movl	-24(%rbp), %eax
	movq	%rsi, %r9
	movq	%rcx, %r8
	movl	%edx, %ecx
	movq	%rdi, %rdx
	movl	%eax, %esi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	head(%rip), %rax
	addq	$96, %rax
	movq	%rax, head(%rip)
	addl	$1, -24(%rbp)
.L11:
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L16
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, head(%rip)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	readnode, .-readnode
	.globl	Hash
	.type	Hash, @function
Hash:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$7, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$400, -4(%rbp)
	jmp	.L18
.L20:
	addq	$1, -24(%rbp)
.L18:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	$47, %al
	je	.L19
	cmpq	$0, -24(%rbp)
	jne	.L20
.L19:
	addq	$1, -24(%rbp)
	jmp	.L21
.L22:
	movl	-12(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -24(%rbp)
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	addl	%ecx, %eax
	movl	%eax, -12(%rbp)
.L21:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L22
	andl	$2147483647, -12(%rbp)
	movl	-4(%rbp), %ecx
	movl	-12(%rbp), %eax
	movl	$0, %edx
	divl	%ecx
	movl	%edx, -12(%rbp)
	movl	-12(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	Hash, .-Hash
	.section	.rodata
	.align 8
.LC7:
	.string	"\n\n\351\207\214\351\235\242\346\234\211\347\233\270\345\220\214\345\255\227\347\254\246\344\270\262 %s \n"
	.text
	.globl	PutHashmap
	.type	PutHashmap, @function
PutHashmap:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	movq	head(%rip), %rcx
	movl	-36(%rbp), %edx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movq	%rax, head(%rip)
	movq	head(%rip), %rax
	movl	80(%rax), %eax
	testl	%eax, %eax
	jne	.L25
	movq	head(%rip), %rax
	leaq	StrTmp(%rip), %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	head(%rip), %rax
	movl	$1, 80(%rax)
	jmp	.L26
.L25:
	movq	head(%rip), %rax
	movq	%rax, -16(%rbp)
	jmp	.L27
.L29:
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	StrTmp(%rip), %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L28
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -20(%rbp)
.L28:
	movq	-16(%rbp), %rax
	movq	88(%rax), %rax
	movq	%rax, -16(%rbp)
.L27:
	cmpq	$0, -16(%rbp)
	jne	.L29
	movq	head(%rip), %rax
	movq	%rax, -16(%rbp)
	jmp	.L30
.L31:
	movq	-16(%rbp), %rax
	movq	88(%rax), %rax
	movq	%rax, -16(%rbp)
.L30:
	movq	-16(%rbp), %rax
	movq	88(%rax), %rax
	testq	%rax, %rax
	jne	.L31
	cmpl	$0, -20(%rbp)
	jne	.L26
	movl	$96, %edi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 88(%rax)
	movq	-16(%rbp), %rax
	movq	88(%rax), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	leaq	StrTmp(%rip), %rsi
	movq	%rax, %rdi
	call	strcpy@PLT
	movq	-16(%rbp), %rax
	movl	$1, 80(%rax)
	movq	-16(%rbp), %rax
	movq	$0, 88(%rax)
	movq	head(%rip), %rax
	movl	80(%rax), %edx
	addl	$1, %edx
	movl	%edx, 80(%rax)
.L26:
	movq	-8(%rbp), %rax
	movq	%rax, head(%rip)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	PutHashmap, .-PutHashmap
	.section	.rodata
	.align 8
.LC8:
	.string	"\n\346\237\245\345\210\260\344\272\206\357\274\214\346\234\211\347\233\270\345\220\214\347\232\204\345\255\227\347\254\246\344\270\262: %s\n"
	.text
	.globl	GetHashNode
	.type	GetHashNode, @function
GetHashNode:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	head(%rip), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	Hash
	movl	%eax, -12(%rbp)
	movq	head(%rip), %rcx
	movl	-12(%rbp), %edx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$5, %rax
	addq	%rcx, %rax
	movq	%rax, head(%rip)
	movq	head(%rip), %rax
	movl	80(%rax), %eax
	testl	%eax, %eax
	je	.L34
	jmp	.L35
.L37:
	movq	head(%rip), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L36
	movq	head(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -16(%rbp)
.L36:
	movq	head(%rip), %rax
	movq	88(%rax), %rax
	movq	%rax, head(%rip)
.L35:
	movq	head(%rip), %rax
	testq	%rax, %rax
	jne	.L37
.L34:
	movq	-8(%rbp), %rax
	movq	%rax, head(%rip)
	movl	-16(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	GetHashNode, .-GetHashNode
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
