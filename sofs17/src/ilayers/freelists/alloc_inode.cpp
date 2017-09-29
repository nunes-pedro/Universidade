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
 * - error ENOSPC should be thrown if there is no free inodes
 * - the allocated inode must be properly initialized
 */
uint32_t soAllocInode(uint32_t type)
{
    soProbe(502, "soAllocInode(%"PRIu32", %p)\n", type);
    return soAllocInodeBin(type);
}
