#include <mlibc/internal-sysdeps.hpp>
#include <mlibc/ansi-sysdeps.hpp>
#if __MLIBC_POSIX_OPTION
#include <mlibc/posix-sysdeps.hpp>
#endif
#include <sys/syscall.h>
#include <mlibc/debug.hpp>
#include <bits/ensure.h>
#include <mlibc/tid.hpp>

void mlibc::sys_libc_log(const char *message) {
	mlibc::sys_write(2, message, strlen(message), nullptr);
}

static void sys_yield() {
	// yield_now@core.proc.Thread://{thread handle}
	uint64_t ret_low, ret_high;
	__syscall_1(
		POPCORN_METHOD_CORE_PROC_THREAD_YIELD_NOW | POPCORN_INTERFACE_CORE_PROC_THREAD,
		ret_low, ret_high,
		mlibc::this_tid(),
		error
	);
	error:
	return;
}

[[noreturn]] void mlibc::sys_libc_panic() {
	asm volatile("ud2");
	while (1) {
		sys_yield();
	}
	__ensure(false);
}

#if __MLIBC_POSIX_OPTION
void mlibc::sys_yield() {
	sys_yield();
}
#endif

[[noreturn]] void mlibc::sys_exit(int status) {
	// exit@core.proc.Thread://{thread handle}
	uint64_t ret_low, ret_high;
	__syscall_2(
		POPCORN_METHOD_CORE_PROC_THREAD_EXIT | POPCORN_INTERFACE_CORE_PROC_THREAD,
		ret_low, ret_high,
		mlibc::this_tid(),
		status,
		error
	);
	error:
	mlibc::panicLogger() << "mlibc: `sys_exit` failed" << frg::endlog;
	mlibc::sys_libc_panic();
}

int mlibc::sys_tcb_set(void *pointer) {
	return mlibc::sys_tcb_set(pointer, mlibc::this_tid());
}

int mlibc::sys_tcb_set(void *pointer, unsigned int tid) {
	// set_tcb@core.proc.Thread://{thread handle}
	uint64_t ret_low, ret_high;
	__syscall_2(
		POPCORN_METHOD_CORE_PROC_THREAD_SET_TCB | POPCORN_INTERFACE_CORE_PROC_THREAD,
		ret_low, ret_high,
		tid,
		pointer,
		error
	);
	return 0;

	error:
	return ret_low;
}

int mlibc::sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
	mlibc::panicLogger() << "mlibc: `sys_futex_wait` is a stub" << frg::endlog;
	//mlibc::sys_libc_panic();
	return -1;
}
int mlibc::sys_futex_wake(int *pointer) {
	mlibc::panicLogger() << "mlibc: `sys_futex_wake` is a stub" << frg::endlog;
	//mlibc::sys_libc_panic();
	return -1;
}

int mlibc::sys_anon_allocate(size_t size, void **pointer) {
	// unstable_anon_alloc@core.proc.Proc://{thread handle}
	uint64_t ret_low, ret_high;
	__syscall_2(
		POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_ALLOC | POPCORN_INTERFACE_CORE_PROC_PROC,
		ret_low, ret_high,
		mlibc::this_tid(),
		size,
		error
	);
	if (pointer) *pointer = reinterpret_cast<void*>(ret_low);
	return 0;

	error:
	return ret_low;
}

int mlibc::sys_anon_free(void *pointer, size_t size) {
	// unstable_anon_dealloc@core.proc.Proc://{thread handle}
	uint64_t ret_low, ret_high;
	__syscall_2(
		POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_DEALLOC | POPCORN_INTERFACE_CORE_PROC_PROC,
		ret_low, ret_high,
		mlibc::this_tid(),
		pointer,
		error
	);
	return 0;

	error:
	return ret_low;
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
	mlibc::infoLogger() << "mlibc: `sys_clock_get` is a stub, returning 0" << frg::endlog;
	//mlibc::sys_libc_panic();
	*secs = 4873292;
	*nanos = 2182;
	return 0;
}
