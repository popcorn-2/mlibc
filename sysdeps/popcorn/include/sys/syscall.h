#ifndef _POPCORN_SYSCALL_H
#define _POPCORN_SYSCALL_H

#include <bits/types.h>
#include <bits/size_t.h>
#include <bits/ssize_t.h>

#define POPCORN_INTERFACE_CORE_IO_WRITE ((__uint128_t)0x3)
#define POPCORN_INTERFACE_CORE_IO_READ ((__uint128_t)0x2)
#define POPCORN_INTERFACE_CORE_IO_SEEK ((__uint128_t)0x4)
#define POPCORN_INTERFACE_CORE_PROC_PROC ((__uint128_t)0xA)
#define POPCORN_INTERFACE_CORE_PROC_THREAD ((__uint128_t)0xA)

#define POPCORN_METHOD_CORE_IO_WRITE_WRITE ((__uint128_t)1 << 96)

#define POPCORN_METHOD_CORE_IO_READ_READ ((__uint128_t)1 << 96)

#define POPCORN_METHOD_CORE_IO_SEEK_SEEK ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_IO_SEEK_TELL ((__uint128_t)2 << 96)

#define POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_ALLOC ((__uint128_t)1 << 96)
#define POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_DEALLOC ((__uint128_t)2 << 96)
#define POPCORN_METHOD_CORE_PROC_THREAD_SET_TCB ((__uint128_t)3 << 96)
#define POPCORN_METHOD_CORE_PROC_THREAD_EXIT ((__uint128_t)7 << 96)
#define POPCORN_METHOD_CORE_PROC_THREAD_YIELD_NOW ((__uint128_t)5 << 96)

#define __syscall_1(uid, ret_low, ret_high, arg0, error) \
	register uint64_t r9 __asm__("r9") = (uint64_t)((uid) >> 64); \
	ret_low = (uint64_t)(uid); \
	uint64_t dummy0, dummy1; \
	asm goto ("clc\n\tsyscall\n\tjc %l7" : "+a"(ret_low), "=d"(ret_high), "=D"(dummy0), "+r"(r9) : "D"(arg0) : "rsi", "rcx", "r8", "r10", "r11", "r12", "memory", "cc" : error);

#define __syscall_2(uid, ret_low, ret_high, arg0, arg1, error) \
	register uint64_t r9 __asm__("r9") = (uint64_t)((uid) >> 64); \
	ret_low = (uint64_t)(uid); \
	uint64_t dummy0, dummy1; \
	asm goto ("clc\n\tsyscall\n\tjc %l9" : "+a"(ret_low), "=d"(ret_high), "=D"(dummy0), "=S"(dummy1), "+r"(r9) : "D"(arg0), "S"(arg1) : "rcx", "r8", "r10", "r11", "r12", "memory", "cc" : error);

#define __syscall_3(uid, ret_low, ret_high, arg0, arg1, arg2, error) \
	register uint64_t r9 __asm__("r9") = (uint64_t)((uid) >> 64); \
	ret_low = (uint64_t)(uid); \
	uint64_t dummy0, dummy1; \
	asm goto ("clc\n\tsyscall\n\tjc %l10" : "+a"(ret_low), "=d"(ret_high), "=D"(dummy0), "=S"(dummy1), "+r"(r9) : "d"(arg2), "D"(arg0), "S"(arg1) : "rcx", "r8", "r10", "r11", "r12", "memory", "cc" : error);

#endif