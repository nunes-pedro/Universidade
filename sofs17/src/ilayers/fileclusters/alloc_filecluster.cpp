/**
 *  \author ...
 *  \tester ...
 */

#include "fileclusters.h"
#include "fileclusters.bin.h"

#include "probing.h"
#include "exception.h"
#include "inode.h"

#include <errno.h>
#include <stdint.h>

#if 0
static void soAllocIndirectFileCluster(SOInode * ip, uint32_t fcn, uint32_t * cnp);
static void soAllocDoubleIndirectFileCluster(SOInode * ip, uint32_t fcn, uint32_t * cnp);
#endif

/* ********************************************************* */

uint32_t soAllocFileCluster(int ih, uint32_t fcn)
{
    soProbe(401, "soAllocFileCluster(%d, %u)\n", ih, fcn);
    return soAllocFileClusterBin(ih, fcn);
}

#if 0
/* ********************************************************* */

/* only a hint to decompose the solution */
static void soAllocIndirectFileCluster(SOInode * ip, uint32_t afcn, uint32_t * cnp)
{
    soProbe(401, "soAllocIndirectFileCluster(%p, %u, %p)\n", ip, afcn, cnp);

    throw SOException(ENOSYS, __FUNCTION__);
}

/* ********************************************************* */

/* only a hint to decompose the solution */
static void soAllocDoubleIndirectFileCluster(SOInode * ip, uint32_t afcn, uint32_t * cnp)
{
    soProbe(401, "soAllocDoubleIndirectFileCluster(%p, %u, %p)\n", ip, afcn, cnp);

    throw SOException(ENOSYS, __FUNCTION__);
}
#endif
