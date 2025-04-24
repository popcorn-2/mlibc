#ifndef _POPCORN_SYSCALL_H
#define _POPCORN_SYSCALL_H

#include <stddef.h>
#include <stdint.h>

#define POPCORN_INTERFACE_CORE_IO_WRITE 0x2
#define POPCORN_INTERFACE_CORE_IO_READ 0x3
#define POPCORN_INTERFACE_CORE_IO_SEEK 0x4
#define POPCORN_INTERFACE_CORE_PROC_PROC 0x5
#define POPCORN_INTERFACE_CORE_PROC_THREAD 0x6

#define POPCORN_METHOD_CORE_IO_WRITE_WRITE 0
#define POPCORN_METHOD_CORE_IO_WRITE_PUT ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_IO_READ_READ 0
#define POPCORN_METHOD_CORE_IO_READ_GET ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_IO_SEEK_SEEK 0
#define POPCORN_METHOD_CORE_IO_SEEK_TELL ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_PROC_PROC_EXIT 0
#define POPCORN_METHOD_CORE_PROC_PROC_DEBUG ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_ALLOC ((__uint128_t)2 << 96)
#define POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_DEALLOC ((__uint128_t)3 << 96)
#define POPCORN_METHOD_CORE_PROC_THREAD_SET_TCB 0

static inline ssize_t __syscall(__uint128_t num, size_t a, size_t b, size_t c, size_t d) {
	typedef uint32_t syscall_num_t __attribute__((vector_size(16)));

	register syscall_num_t num_reg asm("xmm0") = {
		static_cast<uint32_t>(num),
		static_cast<uint32_t>(num >> 32),
		static_cast<uint32_t>(num >> 64),
		static_cast<uint32_t>(num >> 96),
	};
	ssize_t ret;
	asm volatile ("syscall" : "=a"(ret), "=D"(b), "=S"(c), "=d"(d), "=r"(num_reg)
		: "r"(num_reg), "a"(a), "D"(b), "S"(c), "d"(d)
		: "rcx", "r11", "rbx", "memory");; // rcx/r11 used by sysret, rbx used by kernel to save stack pointer
	return ret;
}

#endif