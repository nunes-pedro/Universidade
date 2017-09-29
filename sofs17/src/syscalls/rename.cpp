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
 *  \brief Change the name or the location of a file in the directory hierarchy of the file system.
 *
 *  It tries to emulate <em>rename</em> system call.
 *
 *  \param path path to an existing file
 *  \param newPath new path to the same file in replacement of the old one
 *
 *  \return 0 on success; 
 *      -errno in case of error, being errno the system error that better represents the cause of failure
 */
int soRename(const char *path, const char *newPath)
{
    soProbe(227, "soRename(\"%s\", \"%s\")\n", path, newPath);

    try
    {
        /* replace next line with your code */
        soRenameBin(path, newPath);
    }
    catch(SOException & err)
    {
        return -err.en;
    }

    return 0;
}
