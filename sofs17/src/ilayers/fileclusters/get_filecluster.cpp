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
static uint32_t soGetIndirectFileCluster(SOInode * ip, uint32_t fcn);
static uint32_t soGetDoubleIndirectFileCluster(SOInode * ip, uint32_t fcn);
#endif

/* ********************************************************* */

uint32_t soGetFileCluster(int ih, uint32_t fcn)
{
    soProbe(403, "soGetFileCluster(%d, %u)\n", ih, fcn);
    return soGetFileClusterBin(ih, fcn);
}

#if 0
/* ********************************************************* */

/* only a hint to decompose the solution */
static uint32_t soGetIndirectFileCluster(SOInode * ip, uint32_t fcn);
{
    soProbe(403, "soGetIndirectFileCluster(%p, %u, %p)\n", ip, afcn, cnp);

    throw SOException(ENOSYS, __FUNCTION__);
}

/* ********************************************************* */

/* only a hint to decompose the solution */
static uint32_t soGetDoubleIndirectFileCluster(SOInode * ip, uint32_t fcn);
{
    soProbe(403, "soGetDoubleIndirectFileCluster(%p, %u, %p)\n", ip, afcn, cnp);

    throw SOException(ENOSYS, __FUNCTION__);
}
#endif
