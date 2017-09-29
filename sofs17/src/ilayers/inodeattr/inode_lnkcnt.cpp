#include "inodeattr.h"
#include "inodeattr.bin.h"

#include "probing.h"
#include "datatypes.h"
#include "exception.h"
#include "itdealer.h"

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

/* ************************************** */

uint32_t iIncLnkcnt(int ih)
{
    soProbe(800, "iIncLnkcnt(%d)\n", ih);
    return iIncLnkcntBin(ih);
}

/* ************************************** */

uint32_t iDecLnkcnt(int ih)
{
    soProbe(800, "iDecLnkcnt(%d)\n", ih);
    return iDecLnkcntBin(ih);
}

/* ************************************** */

