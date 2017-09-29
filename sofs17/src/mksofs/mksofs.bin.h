/*
 *  \brief The SOFS17 formatting tool.
 *
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#ifndef __SOFS17_MKSOFS_BIN__
#define __SOFS17_MKSOFS_BIN__

#include "datatypes.h"

void computeStructureBin(uint32_t ntotal, uint32_t itotal,
            uint32_t * itsizep, uint32_t * rmsizep, uint32_t * ctotalp);

void fillInSuperBlockBin(const char *name, uint32_t ntotal, uint32_t itsize, uint32_t rmsize);

void fillInInodeTableBin(uint32_t itstart, uint32_t itsize);

void fillInFreeClusterTableBin(uint32_t rmstart, uint32_t ctotal);

void fillInRootDirBin(uint32_t rtstart);

void resetClustersBin(uint32_t cstart, uint32_t ctotal);

#endif   /* __SOFS17_MKSOFS_BIN__ */
