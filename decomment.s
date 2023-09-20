	.arch armv8-a
	.file	"decomment.c"
	.text
	.align	2
	.global	handleCode
	.type	handleCode, %function
handleCode:
.LFB0:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 47
	bne	.L2
	mov	w0, 2
	str	w0, [sp, 44]
	b	.L3
.L2:
	ldr	w0, [sp, 28]
	cmp	w0, 39
	bne	.L4
	mov	w0, 4
	str	w0, [sp, 44]
	ldr	w0, [sp, 28]
	bl	putchar
	b	.L3
.L4:
	ldr	w0, [sp, 28]
	cmp	w0, 34
	bne	.L5
	mov	w0, 5
	str	w0, [sp, 44]
	ldr	w0, [sp, 28]
	bl	putchar
	b	.L3
.L5:
	str	wzr, [sp, 44]
	ldr	w0, [sp, 28]
	cmn	w0, #1
	beq	.L3
	ldr	w0, [sp, 28]
	bl	putchar
.L3:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	handleCode, .-handleCode
	.section	.rodata
	.align	3
.LC0:
	.string	"/%c"
	.text
	.align	2
	.global	handleSlash
	.type	handleSlash, %function
handleSlash:
.LFB1:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 42
	bne	.L8
	mov	w0, 32
	bl	putchar
	mov	w0, 3
	str	w0, [sp, 44]
	b	.L9
.L8:
	ldr	w0, [sp, 28]
	cmp	w0, 47
	bne	.L10
	mov	w0, 2
	str	w0, [sp, 44]
	mov	w0, 47
	bl	putchar
	b	.L9
.L10:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	bne	.L11
	mov	w0, 2
	str	w0, [sp, 44]
	b	.L9
.L11:
	ldr	w0, [sp, 28]
	cmp	w0, 39
	bne	.L12
	mov	w0, 4
	str	w0, [sp, 44]
	ldr	w1, [sp, 28]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L9
.L12:
	ldr	w0, [sp, 28]
	cmp	w0, 34
	bne	.L13
	mov	w0, 5
	str	w0, [sp, 44]
	ldr	w1, [sp, 28]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L9
.L13:
	str	wzr, [sp, 44]
	ldr	w1, [sp, 28]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
.L9:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE1:
	.size	handleSlash, .-handleSlash
	.align	2
	.global	handleAsterisk
	.type	handleAsterisk, %function
handleAsterisk:
.LFB2:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 42
	bne	.L16
	mov	w0, 3
	str	w0, [sp, 44]
	b	.L17
.L16:
	ldr	w0, [sp, 28]
	cmp	w0, 10
	bne	.L18
	mov	w0, 10
	bl	putchar
	mov	w0, 1
	str	w0, [sp, 44]
	b	.L17
.L18:
	ldr	w0, [sp, 28]
	cmp	w0, 47
	bne	.L19
	str	wzr, [sp, 44]
	b	.L17
.L19:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	bne	.L20
	mov	w0, 8
	str	w0, [sp, 44]
	b	.L17
.L20:
	mov	w0, 1
	str	w0, [sp, 44]
.L17:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2:
	.size	handleAsterisk, .-handleAsterisk
	.align	2
	.global	handleComment
	.type	handleComment, %function
handleComment:
.LFB3:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 42
	bne	.L23
	mov	w0, 3
	str	w0, [sp, 44]
	b	.L24
.L23:
	ldr	w0, [sp, 28]
	cmp	w0, 10
	bne	.L25
	mov	w0, 10
	bl	putchar
	mov	w0, 1
	str	w0, [sp, 44]
	b	.L24
.L25:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	bne	.L26
	mov	w0, 8
	str	w0, [sp, 44]
	b	.L24
.L26:
	mov	w0, 1
	str	w0, [sp, 44]
.L24:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE3:
	.size	handleComment, .-handleComment
	.align	2
	.global	handleLiteral1
	.type	handleLiteral1, %function
handleLiteral1:
.LFB4:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 39
	bne	.L29
	str	wzr, [sp, 44]
	b	.L30
.L29:
	ldr	w0, [sp, 28]
	cmp	w0, 92
	bne	.L31
	mov	w0, 6
	str	w0, [sp, 44]
	b	.L30
.L31:
	mov	w0, 4
	str	w0, [sp, 44]
.L30:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	beq	.L32
	ldr	w0, [sp, 28]
	bl	putchar
.L32:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE4:
	.size	handleLiteral1, .-handleLiteral1
	.align	2
	.global	handleLiteral2
	.type	handleLiteral2, %function
handleLiteral2:
.LFB5:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 34
	bne	.L35
	str	wzr, [sp, 44]
	b	.L36
.L35:
	ldr	w0, [sp, 28]
	cmp	w0, 92
	bne	.L37
	mov	w0, 7
	str	w0, [sp, 44]
	b	.L36
.L37:
	mov	w0, 5
	str	w0, [sp, 44]
.L36:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	beq	.L38
	ldr	w0, [sp, 28]
	bl	putchar
.L38:
	ldr	w0, [sp, 44]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE5:
	.size	handleLiteral2, .-handleLiteral2
	.align	2
	.global	handleBackslash1
	.type	handleBackslash1, %function
handleBackslash1:
.LFB6:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmn	w0, #1
	beq	.L41
	ldr	w0, [sp, 28]
	bl	putchar
.L41:
	mov	w0, 4
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE6:
	.size	handleBackslash1, .-handleBackslash1
	.align	2
	.global	handleBackslash2
	.type	handleBackslash2, %function
handleBackslash2:
.LFB7:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmn	w0, #1
	beq	.L44
	ldr	w0, [sp, 28]
	bl	putchar
.L44:
	mov	w0, 5
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE7:
	.size	handleBackslash2, .-handleBackslash2
	.align	2
	.global	findNewline
	.type	findNewline, %function
findNewline:
.LFB8:
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, 12]
	ldr	w0, [sp, 12]
	cmp	w0, 10
	bne	.L47
	mov	w0, 1
	b	.L48
.L47:
	mov	w0, 0
.L48:
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE8:
	.size	findNewline, .-findNewline
	.section	.rodata
	.align	3
.LC1:
	.string	"Error: line %d: unterminated comment\n"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
.LFB9:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	mov	w0, 1
	str	w0, [sp, 44]
	str	wzr, [sp, 36]
	str	wzr, [sp, 32]
	b	.L50
.L64:
	ldr	w0, [sp, 28]
	bl	findNewline
	mov	w1, w0
	ldr	w0, [sp, 44]
	add	w0, w0, w1
	str	w0, [sp, 44]
	ldr	w0, [sp, 36]
	cmp	w0, 8
	beq	.L67
	ldr	w0, [sp, 36]
	cmp	w0, 8
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 7
	beq	.L53
	ldr	w0, [sp, 36]
	cmp	w0, 7
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 6
	beq	.L54
	ldr	w0, [sp, 36]
	cmp	w0, 6
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 5
	beq	.L55
	ldr	w0, [sp, 36]
	cmp	w0, 5
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 4
	beq	.L56
	ldr	w0, [sp, 36]
	cmp	w0, 4
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 3
	beq	.L57
	ldr	w0, [sp, 36]
	cmp	w0, 3
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 2
	beq	.L58
	ldr	w0, [sp, 36]
	cmp	w0, 2
	bhi	.L52
	ldr	w0, [sp, 36]
	cmp	w0, 0
	beq	.L59
	ldr	w0, [sp, 36]
	cmp	w0, 1
	beq	.L60
	b	.L52
.L59:
	str	wzr, [sp, 32]
	ldr	w0, [sp, 28]
	bl	handleCode
	str	w0, [sp, 36]
	b	.L52
.L60:
	ldr	w0, [sp, 32]
	cmp	w0, 0
	bne	.L61
	ldr	w0, [sp, 44]
	str	w0, [sp, 40]
.L61:
	mov	w0, 1
	str	w0, [sp, 32]
	ldr	w0, [sp, 28]
	bl	handleComment
	str	w0, [sp, 36]
	b	.L52
.L58:
	ldr	w0, [sp, 28]
	bl	handleSlash
	str	w0, [sp, 36]
	b	.L52
.L57:
	ldr	w0, [sp, 28]
	bl	handleAsterisk
	str	w0, [sp, 36]
	b	.L52
.L56:
	ldr	w0, [sp, 28]
	bl	handleLiteral1
	str	w0, [sp, 36]
	b	.L52
.L55:
	ldr	w0, [sp, 28]
	bl	handleLiteral2
	str	w0, [sp, 36]
	b	.L52
.L54:
	ldr	w0, [sp, 28]
	bl	handleBackslash1
	str	w0, [sp, 36]
	b	.L52
.L53:
	ldr	w0, [sp, 28]
	bl	handleBackslash2
	str	w0, [sp, 36]
	b	.L52
.L67:
	nop
.L52:
	ldr	w0, [sp, 28]
	cmn	w0, #1
	bne	.L50
	ldr	w0, [sp, 36]
	cmp	w0, 2
	bne	.L68
	mov	w0, 47
	bl	putchar
	b	.L68
.L50:
	bl	getchar
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	cmp	w0, 0
	bne	.L64
	b	.L63
.L68:
	nop
.L63:
	ldr	w0, [sp, 36]
	cmp	w0, 8
	bne	.L65
	adrp	x0, stderr
	add	x0, x0, :lo12:stderr
	ldr	x3, [x0]
	ldr	w2, [sp, 40]
	adrp	x0, .LC1
	add	x1, x0, :lo12:.LC1
	mov	x0, x3
	bl	fprintf
	mov	w0, 1
	b	.L66
.L65:
	mov	w0, 0
.L66:
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE9:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.3.1 20221121 (Red Hat 11.3.1-4)"
	.section	.note.GNU-stack,"",@progbits
