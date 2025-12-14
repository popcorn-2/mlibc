.section .text
.global __mlibc_start_thread

__mlibc_start_thread:
	pop %rdi
	pop %rsi
	pop %rdx
	xor %ebp, %ebp
	call __mlibc_enter_thread

