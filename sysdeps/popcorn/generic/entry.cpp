
#include <stdint.h>
#include <stdlib.h>
#include <bits/ensure.h>
#include <mlibc/elf/startup.h>
#include <mlibc/ansi-sysdeps.hpp>

// defined by the POSIX library
void __mlibc_initLocale();

extern "C" uintptr_t *__dlapi_entrystack();
extern "C" void __dlapi_enter(uintptr_t *);
void __mlibc_do_finalize();

extern "C" void __mlibc_entry(uintptr_t *entry_stack, int (*main_fn)(int argc, char *argv[])) {
	__dlapi_enter(entry_stack);

	auto result = main_fn(mlibc::entry_stack.argc, mlibc::entry_stack.argv);
	__mlibc_do_finalize();
	mlibc::sys_exit(result);
}
