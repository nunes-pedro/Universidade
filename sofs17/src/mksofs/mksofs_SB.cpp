#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <errno.h>

/* see mksofs.h for a description */
void fillInSuperBlock(const char *name, uint32_t ntotal, uint32_t itsize, uint32_t rmsize)
{
    fillInSuperBlockBin(name, ntotal, itsize, rmsize);
}
