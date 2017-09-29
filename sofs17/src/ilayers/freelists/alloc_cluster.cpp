/**
 *  \author ...
 *  \tester ...
 */

#include "freelists.h"
#include "freelists.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

/*
 * Dictates to be obeyed by the implementation:
 * - error ENOSPC should be thrown if there is no free clusters
 * - after the reference is removed, 
 *      its location should be filled with NullReference
 */
uint32_t soAllocCluster()
{
    soProbe(501, "soAllocCluster()\n");
    return soAllocClusterBin();
}
