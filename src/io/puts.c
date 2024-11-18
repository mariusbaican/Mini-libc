
#include <errno.h>
#include <internal/syscall.h>

int puts(const char *s)
{
    //Determines the length of the string
    int counter = 0;
    char *s_cpy = (char *)s;
    while (*s_cpy != '\0') {
        s_cpy++;
        counter++;
    }

    int ret =  syscall(__NR_write, 1, s, counter + 1);

    if (ret < 0) {
        errno = -ret; //If writing failed it exits
        return -1;
    } else {
        //If it was succesful, print out the end line character
        syscall(__NR_write, 1, "\n", 1);
    }

    return ret;
}
