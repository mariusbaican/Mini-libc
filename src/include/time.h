/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef	TIME_H
#define	TIME_H

#include <internal/types.h>

typedef long int time_t;
struct timespec {
    time_t tv_sec;   // seconds
    long   tv_nsec;  // nanoseconds
};

int nanosleep(const struct timespec *req, struct timespec *rem);
unsigned int sleep(unsigned int seconds);

#endif
