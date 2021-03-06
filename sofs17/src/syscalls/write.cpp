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
 *  \brief Write data into an open regular file.
 *
 *  It tries to emulate <em>write</em> system call.
 *
 *  \param path path to the file
 *  \param buff pointer to the buffer where data to be written is stored
 *  \param count number of bytes to be written
 *  \param pos starting [byte] position in the file data continuum where data is to be written into
 *
 *  \return the number of bytes written, on success; 
 *      -errno in case of error, 
 *      being errno the system error that better represents the cause of failure
 */
int soWrite(const char *path, void *buff, uint32_t count, int32_t pos)
{
    soProbe(230, "soWrite(\"%s\", %p, %u, %u)\n", path, buff, count, pos);

    int ret;
    try
    {
        /* replace next line with your code */
        ret = soWriteBin(path, buff, count, pos);
    }
    catch(SOException & err)
    {
        return -err.en;
    }

    return ret;
}
