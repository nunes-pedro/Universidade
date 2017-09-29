#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <errno.h>

/* see mksofs.h for a description */
void fillInInodeTable(uint32_t itstart, uint32_t itsize)
{
    fillInInodeTableBin(itstart, itsize);
}
