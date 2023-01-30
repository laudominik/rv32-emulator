.global _start
_start:
	addi x1, x0, 1
	addi x2, x0, -1

	bne x1, x2, l1
	jal koniec
l1:
	addi x3, x0, 0xdd
	blt x1, x2, l2
	addi x4, x0, 0xee
	bltu x1, x2, l2
	jal koniec
l2:
	addi x5, x0, 0xaa
koniec:
