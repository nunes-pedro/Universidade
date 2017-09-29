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
 * Even if some of them are not functionally necessary,
 * the following dictates must be obeyed by the implementation:
 * - do nothing if retrieval cache is not empty;
 * - 
 * - after every reference is transferred, 
 *      the previous location should be filled with NullReference
 */
void soReplenish(void)
{
    soProbe(542, "soReplenish()\n");
    soReplenishBin();
}
