/**
 *  \author ...
 *  \tester ...
 */

#include "freelists.h"
#include "freelists.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>
#include <inttypes.h>

/*
 * Dictates to be obeyed by the implementation:
 * - parameter cn must be validated, 
 *      throwing a proper error if necessary
 */
void soFreeCluster(uint32_t cn)
{
    soProbe(531, "soFreeCluster(%"PRIu32")\n", cn);
    soFreeClusterBin(cn);
}

