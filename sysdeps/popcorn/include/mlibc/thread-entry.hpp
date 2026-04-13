#pragma once

#include <mlibc/tcb.hpp>

extern "C" void __mlibc_start_thread(void);
extern "C" void __mlibc_enter_thread(void *(*fn)(void *), void *arg, Tcb *tcb);
