/**
 *  \author ...
 *  \tester ...
 */

#include "fileclusters.h"
#include "fileclusters.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>
#include <inttypes.h>

void soWriteFileCluster(int ih, uint32_t fcn, void *buf)
{
    soProbe(405, "soWriteFileCluster(%d, %u, %p)\n", ih, fcn, buf);
    soWriteFileClusterBin(ih, fcn, buf);
}
