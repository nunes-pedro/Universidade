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
 * - parameter in must be validated, 
 *      throwing a proper error if necessary
 */
void soFreeInode(uint32_t in)
{
    soProbe(532, "soFreeInode(%" PRIu32 ")\n", in);
    soFreeInodeBin(in);
}
