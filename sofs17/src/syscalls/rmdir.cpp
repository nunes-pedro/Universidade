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
 *  \brief Delete a directory.
 *
 *  It tries to emulate <em>rmdir</em> system call.
 *  
 *  The directory should be empty, ie. only containing the '.' and '..' entries.
 *
 *  \param path path to the directory to be deleted
 *
 *  \return 0 on success; 
 *      -errno in case of error, being errno the system error that better represents the cause of failure
 */
int soRmdir(const char *path)
{
    soProbe(233, "soRmdir(\"%s\")\n", path);

    try
    {
        /* replace next line with your code */
        soRmdirBin(path);
    }
    catch(SOException & err)
    {
        return -err.en;
    }

    return 0;
}
