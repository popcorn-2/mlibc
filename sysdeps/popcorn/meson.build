sysdep_supported_options = {
	'posix': false,
	'linux': false,
	'glibc': false,
	'bsd': false,
}

rtld_sources += files(
)

libc_sources += files(
	'generic/entry.cpp',
)

if not no_headers
	install_headers(
		'include/abi-bits/pid_t.h',
		'include/abi-bits/blkcnt_t.h',
		'include/abi-bits/clockid_t.h',
		'include/abi-bits/seek-whence.h',
		'include/abi-bits/limits.h',
		'include/abi-bits/wait.h',
		'include/abi-bits/fcntl.h',
		'include/abi-bits/stat.h',
		'include/abi-bits/signal.h',
		'include/abi-bits/uid_t.h',
		'include/abi-bits/auxv.h',
		'include/abi-bits/dev_t.h',
		'include/abi-bits/nlink_t.h',
		'include/abi-bits/sigevent.h',
		'include/abi-bits/ino_t.h',
		'include/abi-bits/sigval.h',
		'include/abi-bits/blksize_t.h',
		'include/abi-bits/errno.h',
		'include/abi-bits/vm-flags.h',
		'include/abi-bits/mode_t.h',
		'include/abi-bits/gid_t.h',

		subdir: 'abi-bits',
		follow_symlinks: true
	)
	install_headers(
		subdir: 'sys'
	)

	install_headers(
		subdir: 'asm'
	)

	install_headers(
		#'include/linux/fb.h',
		subdir: 'linux'
	)
endif

if not headers_only
	crt = custom_target('crt1',
		build_by_default: true,
		command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
		input: 'crt-x86_64/crt1.S',
		output: 'crt1.o',
		install: true,
		install_dir: get_option('libdir')
	)

	custom_target('crti',
		build_by_default: true,
		command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
		input: 'crt-x86_64/crti.S',
		output: 'crti.o',
		install: true,
		install_dir: get_option('libdir')
	)

	custom_target('crtn',
		build_by_default: true,
		command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
		input: 'crt-x86_64/crtn.S',
		output: 'crtn.o',
		install: true,
		install_dir: get_option('libdir')
	)
endif
