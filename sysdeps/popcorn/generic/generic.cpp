#include <mlibc/internal-sysdeps.hpp>
#include <mlibc/ansi-sysdeps.hpp>
#include <mlibc/syscall.h>
#include <mlibc/debug.hpp>
#include <bits/ensure.h>
#include <mlibc/tid.hpp>

void mlibc::sys_libc_log(const char *message) {
	// debug@core.proc.Proc://{thread handle}
	__syscall(
		POPCORN_METHOD_CORE_PROC_PROC_DEBUG | POPCORN_INTERFACE_CORE_PROC_PROC,
		mlibc::this_tid(),
		0,
		reinterpret_cast<size_t>(message),
		strlen(message)
	);
}

[[noreturn]] void mlibc::sys_libc_panic() {
	while (1) {}
	__ensure(false);
}

[[noreturn]] void mlibc::sys_exit(int status) {
	// exit@core.proc.Proc://{thread handle}
	__syscall(
		POPCORN_METHOD_CORE_PROC_PROC_EXIT | POPCORN_INTERFACE_CORE_PROC_PROC,
		mlibc::this_tid(),
		status,
		0,
		0
	);
	mlibc::panicLogger() << "mlibc: `sys_exit` failed" << frg::endlog;
	__builtin_unreachable();
}

int mlibc::sys_tcb_set(void *pointer) {
	// set_tcb@core.proc.Thread://{thread handle}
	auto res = __syscall(
		POPCORN_METHOD_CORE_PROC_THREAD_SET_TCB | POPCORN_INTERFACE_CORE_PROC_THREAD,
		mlibc::this_tid(),
		reinterpret_cast<size_t>(pointer),
		0,
		0
	);
	if (res < 0) {
		return -res;
	} else {
		return 0;
	}
}

int mlibc::sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
	mlibc::panicLogger() << "mlibc: `sys_futex_wait` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();
}
int mlibc::sys_futex_wake(int *pointer) {
	mlibc::panicLogger() << "mlibc: `sys_futex_wake` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();
}

int mlibc::sys_anon_allocate(size_t size, void **pointer) {
	// unstable_anon_alloc@core.proc.Proc://{thread handle}
	auto res = __syscall(
		POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_ALLOC | POPCORN_INTERFACE_CORE_PROC_PROC,
		mlibc::this_tid(),
		size,
		0,
		0
	);
	if (res < 0) {
		return -res;
	} else {
		*pointer = reinterpret_cast<void*>(res);
		return 0;
	}
}
int mlibc::sys_anon_free(void *pointer, size_t size) {
	// unstable_anon_dealloc@core.proc.Proc://{thread handle}
	auto res = __syscall(
		POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_DEALLOC | POPCORN_INTERFACE_CORE_PROC_PROC,
		mlibc::this_tid(),
		reinterpret_cast<size_t>(pointer),
		0,
		0
	);
	if (res < 0) {
		return -res;
	} else {
		return 0;
	}
}

// mlibc assumes that anonymous memory returned by sys_vm_map() is zeroed by the kernel / whatever is behind the sysdeps
int mlibc::sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
	mlibc::panicLogger() << "mlibc: `sys_vm_map` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();
}
int mlibc::sys_vm_unmap(void *pointer, size_t size) {
	mlibc::panicLogger() << "mlibc: `sys_vm_unmap` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();
}

int mlibc::sys_clock_get(int clock, time_t *secs, long *nanos) {
	mlibc::panicLogger() << "mlibc: `sys_clock_get` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();
}
