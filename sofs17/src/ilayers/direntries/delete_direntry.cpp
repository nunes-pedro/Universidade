/**
 *  \author ...
 *  \tester ...
 */

#include "direntries.h"
#include "direntries.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

uint32_t soDeleteDirEntry(int pih, const char *name, bool clean)
{
    soProbe(353, "soDeleteDirEntry(%d, %s, %s)\n", pih, name, clean ? "true" : "false");
    return soDeleteDirEntryBin(pih, name, clean);
}
