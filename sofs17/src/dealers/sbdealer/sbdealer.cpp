#include "sbdealer.h"

#include "superblock.h"
#include "exception.h"
#include "probing.h"

#include <errno.h>

/* ***************************************** */

void soOpenSBDealer()
{
    soProbe(891, "soOpenSBDealer()\n");
    soOpenSBDealerBin();
}

/* ***************************************** */

void soCloseSBDealer()
{
    soProbe(892, "soCloseSBDealer()\n");
    soCloseSBDealerBin();
}

/* ***************************************** */

SOSuperBlock *sbGetPointer()
{
    soProbe(851, "sbGetPointer()\n");
    return sbGetPointerBin();
}

/* ***************************************** */

void sbSave()
{
    soProbe(852, "sbSaveBin()\n");
    sbSaveBin();
}

/* ***************************************** */
