/**
 *  \author ...
 *  \tester ...
 */

#include "direntries.h"
#include "direntries.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

/* assumes that:
 * - pih is a valid inode handler of a directory where the user has write access
 * - name can already exist or not (that should be tested)
 * - cin is a valid inodo number
 */
void soAddDirEntry(int pih, const char *name, uint32_t cin)
{
    soProbe(352, "soAddDirEntry(%d, %s, %u)\n", pih, name, cin);
    soAddDirEntryBin(pih, name, cin);
}
