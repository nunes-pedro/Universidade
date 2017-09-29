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

void iSetAccess(int ih, uint16_t perm)
{
    soProbe(551, "iSetAccess(%d, 0%o)\n", ih, perm);
    iSetAccessBin(ih, perm);
}

/* ************************************** */

uint16_t iGetAccess(int ih)
{
    soProbe(552, "iGetAccess(%d)\n", ih);
    return iGetAccessBin(ih);
}

/* ************************************** */

bool iCheckAccess(int ih, int access)
{
    soProbe(553, "iCheckAccess(%d, 0%o)\n", ih, access);
    return iCheckAccessBin(ih, access);
}

/* ************************************** */

