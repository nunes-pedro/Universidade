/**
 *  \author ...
 *  \tester ...
 */

#include "direntries.h"
#include "direntries.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

void soRenameDirEntry(int pih, const char *name, const char *newName)
{
    soProbe(354, "soRenameDirEntry(%d, %s, %s)\n", pih, name, newName);
    soRenameDirEntryBin(pih, name, newName);
}
