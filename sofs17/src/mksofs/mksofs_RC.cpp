#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <errno.h>

/* see mksofs.h for a description */
void resetClusters(uint32_t cstart, uint32_t ctotal)
{
    resetClustersBin(cstart, ctotal);
}
