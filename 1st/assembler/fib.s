.section	".rodata"
.align	8
.section	".text"
.global	min_caml_start
min_caml_start:
	addi	%r1, %r0, 20
	sw	%r31, 1(%r30)
	addi	%r30, %r30, 2
	jal	fib.299
	addi	%r30, %r30, -2
	lw	%r31, 1(%r30)
	sw	%r31, 1(%r30)
	addi	%r30, %r30, 2
	jal	min_caml_print_int
	addi	%r30, %r30, -2
	lw	%r31, 1(%r30)
	in	%r1
	j	min_caml_start
fib.299:
	addi	%r26, %r0, 0
	bne	%r1, %r26, beq_else.605
	addi	%r1, %r0, 1
	jr	%r31
beq_else.605:
	addi	%r26, %r0, 1
	bne	%r1, %r26, beq_else.606
	addi	%r1, %r0, 1
	jr	%r31
beq_else.606:
	addi	%r2, %r1, -1
	sw	%r1, 0(%r30)
	addi	%r1, %r2, 0
	sw	%r31, 1(%r30)
	addi	%r30, %r30, 2
	jal	fib.299
	addi	%r30, %r30, -2
	lw	%r31, 1(%r30)
	lw	%r2, 0(%r30)
	addi	%r2, %r2, -2
	sw	%r1, 1(%r30)
	addi	%r1, %r2, 0
	sw	%r31, 2(%r30)
	addi	%r30, %r30, 3
	jal	fib.299
	addi	%r30, %r30, -3
	lw	%r31, 2(%r30)
	lw	%r2, 1(%r30)
	add	%r1, %r2, %r1
	jr	%r31
min_caml_print_int:
	out	%r1
	jr	%r31
