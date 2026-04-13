#pragma once

#include <mlibc/sysdep-signatures.hpp>

namespace mlibc {

struct PopcornSysdepTags :
	LibcLog,
	LibcPanic,
	Exit,
	TcbSet,
	FutexWait,
	FutexWake,
	AnonAllocate,
	AnonFree,
	Open,
	Read,
	Write,
	Seek,
	Close,
	VmMap,
	VmUnmap,
	ClockGet,
	Yield,
	Isatty
{};

template<typename Tag>
using Sysdeps = SysdepOf<PopcornSysdepTags, Tag>;

} // namespace mlibc
