#pragma once

#include <mlibc/all-sysdeps.hpp>
#include <mlibc/thread.hpp>
#include <bits/ensure.h>

namespace mlibc {
	inline unsigned int refetch_tid() {
		if (mlibc::IsImplemented<FutexTid>) {
			return mlibc::sysdep_or_panic<FutexTid>();
		} else {
			#ifdef __POPCORN__
				__ensure(!"tid should always be cached in TCB on popcorn");
			#else
				return 1;
			#endif
		}
	}

	inline unsigned int this_tid() {
		// During RTLD initialization, we don't have a TCB.
		if (mlibc::tcb_available_flag) {
			auto tcb = get_current_tcb();
			return tcb->tid;
		} else {
			return refetch_tid();
		}
	}
} // namespace mlibc
