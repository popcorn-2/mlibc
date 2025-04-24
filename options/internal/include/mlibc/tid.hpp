#pragma once

#include <mlibc/thread.hpp>
#include <mlibc/internal-sysdeps.hpp>

namespace mlibc {
	inline unsigned int this_tid() {
		// During RTLD initialization, we don't have a TCB.
		if (mlibc::tcb_available_flag) {
			auto tcb = get_current_tcb();
			return tcb->tid;
		} else if (mlibc::sys_futex_tid) {
			return mlibc::sys_futex_tid();
		} else {
			#ifdef __POPCORN__
				return 3; // popcorn default tid is 3, because it maps to the thread handle
			#else
				return 1;
			#endif
		}
	}
}
