.global _start
_start:
	jal p
	addi x2, x0, 0xdd
p:	addi x1, x0, 0xcc
	jal x10,q
	addi x3, x0, 0xbb
	nop
q:
	addi x4, x0, 0xee
