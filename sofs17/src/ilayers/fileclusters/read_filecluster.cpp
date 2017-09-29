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

void soReadFileCluster(int ih, uint32_t fcn, void *buf)
{
    soProbe(404, "soReadFileCluster(%d, %u, %p)\n", ih, fcn, buf);
    soReadFileClusterBin(ih, fcn, buf);
}
