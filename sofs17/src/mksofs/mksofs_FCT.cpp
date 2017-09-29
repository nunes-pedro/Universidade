#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <errno.h>

/* see mksofs.h for a description */
void fillInFreeClusterTable(uint32_t rmstart, uint32_t ctotal)
{
    fillInFreeClusterTableBin(rmstart, ctotal);
}
