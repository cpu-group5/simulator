.section	".rodata"
.align	8
.section	".text"
.global	min_caml_start
min_caml_start:
  addi	%r1, %r0, 3
  sw	%r31, 0(%r30)
  addi	%r30, %r30, 1
  jal	double.3
  addi	%r30, %r30, -1
  lw	%r31, 0(%r30)
  sw	%r31, 0(%r30)
  addi	%r30, %r30, 1
  jal	min_caml_print_int
  addi	%r30, %r30, -1
  lw	%r31, 0(%r30)
  double.3:
  add	%r1, %r1, %r1
  jr	%r31
min_caml_print_int:
  out	%r1
  jr	%r31
