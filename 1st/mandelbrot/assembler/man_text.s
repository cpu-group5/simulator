.section	".text"
dbl.38:
	add.s	%f0, %f0, %f0
	jr	%r31
iloop.54:
	addi	%r2, %r0, 0
	bne	%r1, %r2, be_else.126
	addi	%r1, %r0, 1
	j	min_caml_print_int
be_else.126:
	sub.s	%f2, %f3, %f2
	add.s	%f2, %f4, %f2
	sw.s	%f4, 0(%r30)
	sw	%r1, 4(%r30)
	sw.s	%f2, 8(%r30)
	sw.s	%f5, 12(%r30)
	sw.s	%f1, 16(%r30)
	sw	%r31, 20(%r30)
	addi	%r30, %r30, 24
	jal	dbl.38
	addi	%r30, %r30, -24
	lw	%r31, 20(%r30)
	lw.s	%f1, 16(%r30)
	mul.s	%f0, %f1, %f0
	lw.s	%f5, 12(%r30)
	add.s	%f0, %f5, %f1
	lw.s	%f0, 8(%r30)
	mul.s	%f0, %f0, %f2
	mul.s	%f1, %f1, %f3
	add.s	%f2, %f3, %f4
	la	%r1, l.98	lw	%f6, 0(%r1)
	c.le.s	0, %f4, %f6
	bf.s	0, bt.s_else.127
	addi	%r1, %r0, 1
	lw	%r2, 4(%r30)
	sub	%r1, %r2, %r1
	lw.s	%f4, 0(%r30)
	j	iloop.54
bt.s_else.127:
	addi	%r1, %r0, 0
	j	min_caml_print_int
xloop.44:
	addi	%r3, %r0, 400
	slt	%r28, %r3, %r1
	beq	%r28, %r1, bne_else.128
	jr	%r31
bne_else.128:
	sw	%r1, 0(%r30)
	sw	%r2, 4(%r30)
	sw	%r31, 12(%r30)
	addi	%r30, %r30, 16
	jal	min_caml_float_of_int
	addi	%r30, %r30, -16
	lw	%r31, 12(%r30)
	sw	%r31, 12(%r30)
	addi	%r30, %r30, 16
	jal	dbl.38
	addi	%r30, %r30, -16
	lw	%r31, 12(%r30)
	la	%r1, l.100	lw	%f1, 0(%r1)
	inv.s	%f31, %f1
	mul.s	%f0, %f31, %f0
	la	%r1, l.102	lw	%f1, 0(%r1)
	sub.s	%f0, %f1, %f0
	lw	%r1, 4(%r30)
	sw.s	%f0, 8(%r30)
	sw	%r31, 12(%r30)
	addi	%r30, %r30, 16
	jal	min_caml_float_of_int
	addi	%r30, %r30, -16
	lw	%r31, 12(%r30)
	sw	%r31, 12(%r30)
	addi	%r30, %r30, 16
	jal	dbl.38
	addi	%r30, %r30, -16
	lw	%r31, 12(%r30)
	la	%r1, l.100	lw	%f1, 0(%r1)
	inv.s	%f31, %f1
	mul.s	%f0, %f31, %f0
	la	%r1, l.105	lw	%f1, 0(%r1)
	sub.s	%f0, %f1, %f5
	addi	%r1, %r0, 1000
	la	%r2, l.107	lw	%f0, 0(%r2)
	la	%r2, l.107	lw	%f1, 0(%r2)
	la	%r2, l.107	lw	%f2, 0(%r2)
	la	%r2, l.107	lw	%f3, 0(%r2)
	lw.s	%f4, 8(%r30)
	sw	%r31, 12(%r30)
	addi	%r30, %r30, 16
	jal	iloop.54
	addi	%r30, %r30, -16
	lw	%r31, 12(%r30)
	addi	%r1, %r0, 1
	lw	%r2, 0(%r30)
	add	%r1, %r2, %r1
	lw	%r2, 4(%r30)
	j	xloop.44
yloop.40:
	addi	%r2, %r0, 400
	slt	%r28, %r2, %r1
	beq	%r28, %r1, bne_else.130
	jr	%r31
bne_else.130:
	addi	%r2, %r0, 0
	sw	%r1, 0(%r30)
	addi	%r26, %r2, 0
	addi	%r2, %r1, 0
	addi	%r1, %r26, 0
	sw	%r31, 4(%r30)
	addi	%r30, %r30, 8
	jal	xloop.44
	addi	%r30, %r30, -8
	lw	%r31, 4(%r30)
	addi	%r1, %r0, 1
	lw	%r2, 0(%r30)
	add	%r1, %r2, %r1
	j	yloop.40
.global	min_caml_start
min_caml_start:
	addi	%r1, %r0, 0
	sw	%r31, 4(%r30)
	addi	%r30, %r30, 8
	jal	yloop.40
	addi	%r30, %r30, -8
	lw	%r31, 4(%r30)
	hlt
