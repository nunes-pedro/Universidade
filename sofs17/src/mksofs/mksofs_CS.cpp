#include "mksofs.h"
#include "mksofs.bin.h"

#include "datatypes.h"
#include "rawdisk.h"
#include "exception.h"

#include <inttypes.h>
#include <errno.h>

/* see mksofs.h for a description */
void computeStructure(uint32_t ntotal, uint32_t itotal,
            uint32_t * itsizep, uint32_t * rmsizep, uint32_t * ctotalp)
{
    computeStructureBin(ntotal, itotal, itsizep, rmsizep, ctotalp);
}
