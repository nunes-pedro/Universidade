#include "czdealer.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

/* ***************************************** */

void soOpenCZDealer()
{
    soColorProbe(791, BLUE, "soOpenCZDealer()\n");
    soOpenCZDealerBin();
}

/* ***************************************** */

void soCloseCZDealer()
{
    soColorProbe(792, BLUE, "soCloseCZDealer()\n");
    soCloseCZDealerBin();
}

/* ***************************************** */

void soReadCluster(uint32_t n, void *buf)
{
    soColorProbe(771, BLUE, "soReadCluster(%u, %p)\n", n, buf);
    soReadClusterBin(n, buf);
}

/* ***************************************** */

void soWriteCluster(uint32_t n, void *buf)
{
    soColorProbe(772, BLUE, "soWriteCluster(%u, %p)\n", n, buf);
    soWriteClusterBin(n, buf);
}

/* ***************************************** */

uint32_t soGetMaxFileSize()
{
    return soGetMaxFileSizeBin();
}

/* ***************************************** */

