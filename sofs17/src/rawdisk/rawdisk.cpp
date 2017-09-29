 /*
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#include "rawdisk.h"

#include "probing.h"
#include "exception.h"

#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

/* ********************************************* */

/* Internal data structure */

/* File descriptor of the Linux file that simulates the disk */
static int fd = -1;

/* Total number of blocks of the storage device */
static uint32_t ntotal = 0;

/* ********************************************* */

void soOpenRawDisk(const char *devname, uint32_t * np)
{
    soColorProbe(991, GREEN, "soOpenRawDisk(\"%s\", %p)\n", devname, np);

    /* check devname */
    if (devname == NULL)
        throw SOException(EINVAL, __FUNCTION__);

    /* fail if device already open */
    if (fd != -1)
        throw SOException(EBUSY, __FUNCTION__);

    /* opening supporting file in async mode for read and write */
    if ((fd = open(devname, O_RDWR)) == -1)
        throw SOException(errno, __FUNCTION__); /* checking for opening error */

    /* checking device for conformity */
    struct stat st;
    if (stat(devname, &st) == -1)
        throw SOException(errno, __FUNCTION__);
    if ((st.st_size % BlockSize) != 0)
        throw SOException(EMEDIUMTYPE, __FUNCTION__);

    /* get number of blocks of the device */
    ntotal = st.st_size / BlockSize;

    /* return number of blocks, if requested */
    if (np != NULL)
        *np = ntotal;
}

/* ********************************************* */

void soCloseRawDisk(void)
{
    soColorProbe(992, GREEN, "soCloseRawDisk()\n");

    /* checking for device close state */
    if (fd == -1)
        throw SOException(EBADF, __FUNCTION__);

    /* close the device */
    close(fd);
    ntotal = 0;
    fd = -1;
}

/* ********************************************* */

void soReadRawBlock(uint32_t n, void *buf)
{
    soColorProbe(951, GREEN, "soReadRawBlock(%" PRIu32 ", %p)\n", n, buf);

    /* checking arguments */
    if (buf == NULL)
        throw SOException(EINVAL, __FUNCTION__);

    if (n >= ntotal)
        throw SOException(EINVAL, __FUNCTION__);

    if (fd == -1)
        throw SOException(EBADF, __FUNCTION__);

    /* transfer block data */
    if (lseek(fd, BlockSize * n, SEEK_SET) == -1)
        throw SOException(errno, __FUNCTION__);

    if (read(fd, buf, BlockSize) != BlockSize)
        throw SOException(EIO, __FUNCTION__);
}

/* ********************************************* */

void soWriteRawBlock(uint32_t n, void *buf)
{
    soColorProbe(952, GREEN, "soWriteRawBlock(%" PRIu32 ", %p)\n", n, buf);

    /* checking arguments */
    if (buf == NULL)
        throw SOException(EINVAL, __FUNCTION__);

    if (n >= ntotal)
        throw SOException(EINVAL, __FUNCTION__);

    if (fd == -1)
        throw SOException(EBADF, __FUNCTION__);

    /* transfer block data */
    if (lseek(fd, BlockSize * n, SEEK_SET) == -1)
        throw SOException(errno, __FUNCTION__);
    if (write(fd, buf, BlockSize) != BlockSize)
        throw SOException(EIO, __FUNCTION__);
}

/* ********************************************* */

