// SPDX-License-Identifier: BSD-3-Clause

#include <time.h>
#include <errno.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    //This just makes use of the nanosleep syscall
    int ret = syscall(__NR_nanosleep, req, rem);

    if (ret < 0) {
        errno = -ret;
        return -1;
    }
    return 0;
}

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;

    req.tv_sec = seconds;
    req.tv_nsec = 0;

    //Handle nanosleep interruption
    while (nanosleep(&req, &rem) == -1) {
        if (errno == EINTR) { //If its interrupted by a signal
            req = rem;        //it sets req to remaining time
        } else {
            return req.tv_sec; //Otherwise it returns the remaining time
        }
    }

    return 0; //Return 0 if nanosleep was succesfull
}
