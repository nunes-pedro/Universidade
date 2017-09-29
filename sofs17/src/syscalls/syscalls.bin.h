/*
 *  \brief Set of sofs17 system calls, binary version
 *
 *  The aim is to provide a unique description of the functions that operate at this level.
 *
 *  \author Artur Pereira 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva 2009, 2017
 *  \author António Rui Borges - 2010--2015
 */

#ifndef __SOFS17_SYSCALLS_BIN__
#define __SOFS17_SYSCALLS_BIN__

#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <libgen.h>

int soLinkBin(const char *path, const char *newPath);
int soUnlinkBin(const char *path);
int soRenameBin(const char *path, const char *newPath);
int soMknodBin(const char *path, mode_t mode);
int soReadBin(const char *path, void *buff, uint32_t count, int32_t pos);
int soWriteBin(const char *path, void *buff, uint32_t count, int32_t pos);
int soTruncateBin(const char *path, off_t length);
int soMkdirBin(const char *path, mode_t mode);
int soRmdirBin(const char *path);
int soReaddirBin(const char *path, void *buff, int32_t pos);
int soSymlinkBin(const char *effPath, const char *path);
int soReadlinkBin(const char *path, char *buff, size_t size);

#endif                          /* __SOFS17_SYSCALLS_BIN__ */
