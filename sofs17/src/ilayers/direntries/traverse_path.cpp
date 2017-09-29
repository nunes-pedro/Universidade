/**
 *  \author ...
 *  \tester ...
 */

#include "direntries.h"
#include "direntries.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

uint32_t soTraversePath(char *path)
{
    soProbe(301, "soTraversePath(%s)\n", path);
    return soTraversePathBin(path);
}
