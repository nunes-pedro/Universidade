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
 *  \brief Create a regular file with size 0.
 *
 *  It tries to emulate <em>mknod</em> system call.
 *
 *  \param path path to the file
 *  \param mode type and permissions to be set:
 *                    a bitwise combination of S_IFREG, S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH,
 *                    S_IWOTH, S_IXOTH
 *
 *  \return 0 on success; 
 *      -errno in case of error, being errno the system error that better represents the cause of failure
 */
int soMknod(const char *path, mode_t mode)
{
    soProbe(228, "soMknod(\"%s\", %u)\n", path, mode);

    try
    {
        /* replace next line with your code */
        soMknodBin(path, mode);
    }
    catch(SOException & err)
    {
        return -err.en;
    }

    return 0;
}
