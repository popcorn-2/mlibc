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
#define POPCORN_METHOD_CORE_PROC_THREAD_MAP_VMO ((__uint128_t)9 << 96)

#define SYSCALL_CLOBBERS "rcx", "r11", "r12", "memory", "cc"

// Base macro to handle the common 128-bit UID and Return logic
#define __syscall_asm(instr, lo, hi, a0, a1, a2, r8_val, r9_val, r10_val, error_label) \
    asm goto (                                                                 \
        instr "\n\t"                                                           \
        "syscall\n\t"                                                          \
        "jc %l14"                                              \
        : "+a"(lo), "=d"(hi), "+D"(a0), "+S"(a1), "+r"(r8_val), "+r"(r9_val), "+r"(r10_val)   \
        : "d"(a2)                                                              \
        : SYSCALL_CLOBBERS                                                     \
        : error_label                                                          \
    )

// 0 Args
#define syscall0(uid, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t _a0, _a1, _a2; \
    register uint64_t _r8 __asm__("r8"), _r10 __asm__("r10"); \
    __syscall_asm("clc", lo, hi, _a0, _a1, _a2, _r8, _r9, _r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

// 1 Arg
#define syscall1(uid, arg0, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t a0 = (uint64_t)(arg0), _a1, _a2; \
    register uint64_t _r8 __asm__("r8"), _r10 __asm__("r10"); \
    __syscall_asm("clc", lo, hi, a0, _a1, _a2, _r8, _r9, _r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

// 2 Args
#define syscall2(uid, arg0, arg1, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t a0 = (uint64_t)(arg0), a1 = (uint64_t)(arg1), _a2; \
    register uint64_t _r8 __asm__("r8"), _r10 __asm__("r10"); \
    __syscall_asm("clc", lo, hi, a0, a1, _a2, _r8, _r9, _r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

// 3 Args
#define syscall3(uid, arg0, arg1, arg2, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t a0 = (uint64_t)(arg0), a1 = (uint64_t)(arg1), a2 = (uint64_t)(arg2); \
    register uint64_t _r8 __asm__("r8"), _r10 __asm__("r10"); \
    __syscall_asm("clc", lo, hi, a0, a1, a2, _r8, _r9, _r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

// 4 Args
#define syscall4(uid, arg0, arg1, arg2, arg3, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t a0 = (uint64_t)(arg0), a1 = (uint64_t)(arg1), a2 = (uint64_t)(arg2); \
    register uint64_t r10 __asm__("r10") = (uint64_t)(arg3), _r8 __asm__("r8"); \
    __syscall_asm("clc", lo, hi, a0, a1, a2, _r8, _r9, r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

// 5 Args
#define syscall5(uid, arg0, arg1, arg2, arg3, arg4, out_val, err_lbl) do { \
    uint64_t lo = (uint64_t)(uid), hi; \
    register uint64_t _r9 __asm__("r9") = (uint64_t)((__uint128_t)(uid) >> 64); \
    uint64_t a0 = (uint64_t)(arg0), a1 = (uint64_t)(arg1), a2 = (uint64_t)(arg2); \
    register uint64_t r10 __asm__("r10") = (uint64_t)(arg3); \
    register uint64_t r8 __asm__("r8") = (uint64_t)(arg4); \
    __syscall_asm("clc", lo, hi, a0, a1, a2, r8, _r9, r10, err_lbl); \
    out_val = ((__uint128_t)hi << 64) | lo; \
} while(0)

#endif