/**
 *  \author ...
 *  \tester ...
 */

#include "fileclusters.h"
#include "fileclusters.bin.h"

#include "probing.h"
#include "exception.h"
#include "datatypes.h"

#include <errno.h>
#include <stdint.h>

#if 0
static void soFreeIndirectFileClusters(SOInode * ip, uint32_t ffcn);
static void soFreeDoubleIndirectFileClusters(SOInode * ip, uint32_t ffcn);
#endif

/* ********************************************************* */

void soFreeFileClusters(int ih, uint32_t ffcn)
{
    soProbe(402, "soFreeFileClusters(%d, %u)\n", ih, ffcn);
    soFreeFileClustersBin(ih, ffcn);
}

#if 0
/* ********************************************************* */

/* only a hint to decompose the solution */
static void soFreeIndirectFileClusters(SOInode * ip, uint32_t ffcn)
{
    soProbe(402, "soFreeIndirectFileClusters(%p, %u)\n", ip, ffcn);

    throw SOException(ENOSYS, __FUNCTION__);
}

/* ********************************************************* */

/* only a hint to decompose the solution */
static void soFreeDoubleIndirectFileClusters(SOInode * ip, uint32_t ffcn)
{
    soProbe(402, "soFreeDoubleIndirectFileClusters(%p, %u)\n", ip, ffcn);

    throw SOException(ENOSYS, __FUNCTION__);
}
#endif

/* ********************************************************* */
