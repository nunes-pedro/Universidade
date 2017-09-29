#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <errno.h>

/* see mksofs.h for a description */
void fillInRootDir(uint32_t rtstart)
{
    fillInRootDirBin(rtstart);
}
