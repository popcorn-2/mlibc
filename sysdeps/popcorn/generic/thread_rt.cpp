#include <mlibc/tcb.hpp>
#include <mlibc/thread-entry.hpp>
#include <mlibc/all-sysdeps.hpp>
#include <bits/ensure.h>

extern "C" void __mlibc_enter_thread(void *(*fn)(void *), void *arg, Tcb *tcb) {
    // Wait until our parent sets up the TID:
    while(__atomic_load_n(&tcb->tid, __ATOMIC_RELAXED) == 0)
		mlibc::sysdep<FutexWait>(&tcb->tid, 0, nullptr);

    if(mlibc::sysdep<TcbSet>(tcb))
		__ensure(!"failed to set tcb for new thread");

	// Enable cancellation once the TCB is up
	__atomic_fetch_or(&tcb->cancelBits, tcbCancelEnableBit, __ATOMIC_RELAXED);

	tcb->invokeThreadFunc(reinterpret_cast<void *>(fn), arg);

    __atomic_store_n(&tcb->didExit, 1, __ATOMIC_RELEASE);
    mlibc::sysdep<FutexWake>(&tcb->didExit, true);

	mlibc::thread_exit(tcb->returnValue);
}
