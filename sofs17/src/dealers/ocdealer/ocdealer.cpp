#include "ocdealer.h"

#include "probing.h"
#include "sbdealer.h"
#include "itdealer.h"
#include "czdealer.h"
#include "rawdisk.h"

#include <stdint.h>

void soOpenDisk(const char *devname, uint32_t * ntp)
{
    soColorProbe(691, GREEN, "soOpenDisk(\"%s\", %p)\n", devname, ntp);

    /* call lower level openning function */
    soOpenRawDisk(devname, ntp);

    /* open dealers */
    soOpenSBDealer();
    soOpenITDealer();
    soOpenCZDealer();
}

void soCloseDisk()
{
    soColorProbe(692, GREEN, "soCloseDisk()\n");

    /* flush dealers */
    soCloseCZDealer();
    soCloseITDealer();
    soCloseSBDealer();

    /* call lower level closing function */
    soCloseRawDisk();
}
