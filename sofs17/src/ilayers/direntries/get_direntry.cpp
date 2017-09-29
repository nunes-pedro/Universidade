/**
 *  \author ...
 *  \tester ...
 */

#include "direntries.h"
#include "direntries.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

uint32_t soGetDirEntry(int pih, const char *name)
{
    soProbe(351, "soGetDirEntry(%d, %s)\n", pih, name);
    return soGetDirEntryBin(pih, name);
}
