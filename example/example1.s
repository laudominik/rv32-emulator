.global _start
_start:

	addi x1, x0, 7
	addi x2, x0, 0xcc

	csrrw x0, 0, x1
    csrrwi x0, 1, 5
    csrrwi x0, 2, 0x1e

    csrrs x3, 0, x2
    csrrc x4, 1, x1
    csrrsi x5, 2, 1

