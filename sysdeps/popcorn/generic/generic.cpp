#include <mlibc/all-sysdeps.hpp>
#include <sys/syscall.h>
#include <mlibc/debug.hpp>
#include <bits/ensure.h>
#include <mlibc/tid.hpp>
#include <mlibc/tcb.hpp>
#include <stdio.h>

namespace mlibc {
	void Sysdeps<LibcLog>::operator()(const char *message) {
		mlibc::sysdep<Write>(2, message, strlen(message), nullptr);
	}

	[[noreturn]] void Sysdeps<LibcPanic>::operator()() {
		asm volatile("ud2");
		while (1) {
			Sysdeps<Yield>();
		}
		__ensure(false);
	}

	void Sysdeps<Yield>::operator()() {
		// yield_now@core.proc.Thread://{thread handle}
		__uint128_t ret;
		syscall1(
			POPCORN_METHOD_CORE_PROC_THREAD_YIELD_NOW | POPCORN_INTERFACE_CORE_PROC_THREAD,
			mlibc::this_tid(),
			ret,
			error
		);
		error:
		return;
	}

	[[noreturn]] void Sysdeps<Exit>::operator()(int status) {
		// exit@core.proc.Thread://{thread handle}
		__uint128_t ret;
		syscall2(
			POPCORN_METHOD_CORE_PROC_THREAD_EXIT | POPCORN_INTERFACE_CORE_PROC_THREAD,
			mlibc::this_tid(),
			status,
			ret,
			error
		);
		error:
		mlibc::panicLogger() << "mlibc: `sys_exit` failed" << frg::endlog;
	}

	int Sysdeps<TcbSet>::operator()(void *pointer) {
		// set_tcb@core.proc.Thread://{thread handle}
		__uint128_t ret;
		syscall2(
			POPCORN_METHOD_CORE_PROC_THREAD_SET_TCB | POPCORN_INTERFACE_CORE_PROC_THREAD,
			reinterpret_cast<Tcb*>(pointer)->tid,
			pointer,
			ret,
			error
		);
		return 0;

		error:
		return ret;
	}

	int Sysdeps<FutexWait>::operator()(int *pointer, int expected, const struct timespec *time) {
		mlibc::panicLogger() << "mlibc: `sys_futex_wait` is a stub" << frg::endlog;
	}
	int Sysdeps<FutexWake>::operator()(int *pointer, bool all) {
		mlibc::panicLogger() << "mlibc: `sys_futex_wake` is a stub" << frg::endlog;
	}

	namespace {
		int size_t_to_str(size_t val, char* buf) {
			int len = 0;

			// Handle zero explicitly
			if (val == 0) {
				buf[len++] = '0';
				buf[len] = '\0';
				return len;
			}

			// Extract digits in reverse order
			while (val > 0) {
				buf[len++] = (val % 10) + '0';
				val /= 10;
			}

			// Reverse the string in place to fix the order
			int start = 0;
			int end = len - 1;
			while (start < end) {
				char temp = buf[start];
				buf[start] = buf[end];
				buf[end] = temp;
				start++;
				end--;
			}

			return len; // Returns the count of characters
		}
	}

	int Sysdeps<AnonAllocate>::operator()(size_t size, void **pointer) {
		static char buf[32] = "mem:z/";

		auto ret = size_t_to_str(size, buf+6);

		// open@core.mem.Pager
		const static __uint128_t proto[1] = {
			6
		};

		__uint128_t ret3;
		syscall4(
			((__uint128_t)1 << 96),
			buf,
			ret+6,
			proto,
			1,
			ret3,
			error
		);

		{
			// map_vmo@core.proc.Proc://{thread handle}
			__uint128_t ret2;
			syscall5(
				POPCORN_METHOD_CORE_PROC_THREAD_MAP_VMO | POPCORN_INTERFACE_CORE_PROC_PROC,
				mlibc::this_tid(),
				static_cast<size_t>(ret3),
				NULL,
				size,
				0,
				ret2,
				error2
			);
			if (pointer) *pointer = reinterpret_cast<void*>(static_cast<size_t>(ret2));
			return 0;

			error2:
			return ret2;
		}

		error:
		return ret3;
	}

	int Sysdeps<AnonFree>::operator()(void *pointer, size_t size) {
		// unstable_anon_dealloc@core.proc.Proc://{thread handle}
		/*__uint128_t ret;
		syscall2(
			POPCORN_METHOD_CORE_PROC_PROC_UNSTABLE_ANON_DEALLOC | POPCORN_INTERFACE_CORE_PROC_PROC,
			mlibc::this_tid(),
			pointer,
			ret,
			error
		);*/
		return 0;

		//error:
		//return ret;
	}

	// mlibc assumes that anonymous memory returned by sys_vm_map() is zeroed by the kernel / whatever is behind the sysdeps
	int Sysdeps<VmMap>::operator()(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
		mlibc::panicLogger() << "mlibc: `sys_vm_map` is a stub" << frg::endlog;
	}
	int Sysdeps<VmUnmap>::operator()(void *pointer, size_t size) {
		mlibc::panicLogger() << "mlibc: `sys_vm_unmap` is a stub" << frg::endlog;
	}

	int Sysdeps<ClockGet>::operator()(int clock, time_t *secs, long *nanos) {
		mlibc::infoLogger() << "mlibc: `sys_clock_get` is a stub, returning 0" << frg::endlog;
		//mlibc::sys_libc_panic();
		*secs = 4873292;
		*nanos = 2182;
		return 0;
	}
}
