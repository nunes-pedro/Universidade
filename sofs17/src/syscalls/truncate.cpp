/*
 * \author ...
 */

#include "syscalls.h"
#include "syscalls.bin.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <libgen.h>
#include <string.h>

#include "probing.h"
#include "exception.h"

/*
 *  \brief Truncate a regular file to a specified length.
 *
 *  It tries to emulate <em>truncate</em> system call.
 *
 *  \param path path to the file
 *  \param length new size for the regular size
 *
 *  \return 0 on success; 
 *      -errno in case of error, being errno the system error that better represents the cause of failure
 */
int soTruncate(const char *path, off_t length)
{
    soProbe(231, "soTruncate(\"%s\", %u)\n", path, length);

    try
    {
        /* replace next line with your code */
        soTruncateBin(path, length);
    }
    catch(SOException & err)
    {
        return -err.en;
    }

    return 0;
}
