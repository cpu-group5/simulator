.section	".rodata"
.align	8
.section	".text"
.global	min_caml_start
min_caml_start:
	addi	%r1, %r0, 21600
    addi	%r2, %r0, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
    addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	addi	%r2, %r2, 16875
	sw	%r31, 0(%r30)
	addi	%r30, %r30, 1
	jal	gcd.180
	addi	%r30, %r30, -1
	lw	%r31, 0(%r30)
	sw	%r31, 0(%r30)
	addi	%r30, %r30, 1
	out %r1
	addi	%r30, %r30, -1
	lw	%r31, 0(%r30)
    hlt
gcd.180:
	slti	%r28, %r1, 0
	beq	%r28, %r0, bne_else.342
	add	%r1, %r0, %r2
	jr	%r31
bne_else.342:
	slt	%r28, %r1, %r2
	beq	%r28, %r0, bne_else.343
	sub	%r2, %r2, %r1
	j	gcd.180
bne_else.343:
	sub	%r1, %r1, %r2
	addi	%r26, %r2, 0
	addi	%r2, %r1, 0
	addi	%r1, %r26, 0
	j	gcd.180
