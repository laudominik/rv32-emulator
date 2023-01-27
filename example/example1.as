.global _boot

.text

_boot:
	addi x1, x0, 0x123
	slli x1, x1, 12
	addi x1, x1, 0x256
	sb x1, 512(x0)
	sh x1, 64(x0)
	sw x1, 728(x0)


