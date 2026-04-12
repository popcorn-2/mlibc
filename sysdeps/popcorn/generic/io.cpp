#include <mlibc/internal-sysdeps.hpp>
#include <mlibc/ansi-sysdeps.hpp>
#include <abi-bits/fcntl.h>
#include <sys/syscall.h>
#include <string.h>
#include <bits/ensure.h>
#include <mlibc/debug.hpp>
#include <errno.h>

int mlibc::sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
	mlibc::panicLogger() << "mlibc: `sys_open` is a stub" << frg::endlog;
	mlibc::sys_libc_panic();

	/*const static __uint128_t protocols[2] = {
		POPCORN_INTERFACE_CORE_IO_READ,
		POPCORN_INTERFACE_CORE_IO_WRITE
	};

	size_t offset, len;
	if ((mode & 0b11) == O_RDONLY) {
		offset = 0;
		len = 1;
	} else if ((mode & 0b11) == O_WRONLY) {
		offset = 1;
		len = 1;
	} else {
		__ensure((mode & 0b11) == O_RDWR);
		offset = 0;
		len = 2;
	}

	auto res = __syscall(
		0,
		reinterpret_cast<size_t>(pathname),
		strlen(pathname),
		reinterpret_cast<size_t>(protocols + offset),
		len
	);
	if (res < 0) {
		return -res;
	} else {
		*fd = res;
		return 0;
	}*/
}

int mlibc::sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
	__uint128_t ret;
	syscall3(
		POPCORN_METHOD_CORE_IO_READ_READ | POPCORN_INTERFACE_CORE_IO_READ,
		fd,
		buf,
		count,
		ret,
		error
	);
	if (bytes_read) *bytes_read = static_cast<ssize_t>(ret);
	return 0;

	error:
	return ret;
}

int mlibc::sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
	__uint128_t ret;
	syscall3(
		POPCORN_METHOD_CORE_IO_WRITE_WRITE | POPCORN_INTERFACE_CORE_IO_WRITE,
		fd,
		buf,
		count,
		ret,
		error
	);
	if (bytes_written) *bytes_written = static_cast<ssize_t>(ret);
	return 0;

	error:
	return ret;
}

int mlibc::sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
	mlibc::infoLogger() << "mlibc: `sys_seek` is a stub" << frg::endlog;
	//mlibc::sys_libc_panic();
	return ESPIPE; // HACKY
}

int mlibc::sys_close(int fd) {
	mlibc::panicLogger() << "mlibc: `sys_close` is a stub" << frg::endlog;
}
