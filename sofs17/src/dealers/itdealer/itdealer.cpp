#include "itdealer.h"
#include "itdealer.bin.h"

#include "probing.h"
#include "exception.h"

#include <errno.h>

/* ************************************** */

void soOpenITDealer()
{
    soProbe(721, "soOpenITDealer()\n");
    soOpenITDealerBin();
}

/* ************************************** */

void soCloseITDealer()
{
    soProbe(722, "soCloseITDealer()\n");
    soCloseITDealerBin();
}

/* ************************************** */

int iOpen(uint32_t in)
{
    soProbe(711, "iOpen(%u)\n", in);
    return iOpenBin(in);
}

/* ************************************** */
void iCheckHandler(int ih, const char * funcname)
{
    soProbe(721, "iCheckHandler(%d)\n", ih);
    iCheckHandlerBin(ih);
}

/* ************************************** */

SOInode *iGetPointer(int ih)
{
    soProbe(712, "iGetPointer(%d)\n", ih);
    return iGetPointerBin(ih);
}

/* ************************************** */

void iSave(int ih)
{
    soProbe(713, "iSave(%d)\n", ih);
    iSaveBin(ih);
}

/* ************************************** */

void iClose(int ih)
{
    soProbe(714, "iClose(%d)\n", ih);
    iCloseBin(ih);
}

/* ************************************** */

uint32_t iGetInodeNumber(int ih)
{
    soProbe(720, "iGetInodeNumber(%d)\n", ih);
    return iGetInodeNumberBin(ih);
}

/* ************************************** */
