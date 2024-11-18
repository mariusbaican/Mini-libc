// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	int ret = syscall(__NR_lseek, fd, offset, whence);

	if (ret < 0) {
		errno = -ret;
		return (off_t)-1;
	}

	return (off_t)ret;
}
