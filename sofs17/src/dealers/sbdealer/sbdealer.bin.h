/*
 *  \file sbdealer.h
 *  \brief superblock dealer: mediates access to the disk superblock
 *
 *  This module guarantees that only a single copy of the superblock is in memory,
 *  thus improving its consistency.
 *
 *  \remarks In case an error occurs, every function throws a SOException
 *
 *  \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_SBDEALER_BIN__
#define __SOFS17_SBDEALER_BIN__

#include "superblock.h"

#include <stdint.h>

/* ***************************************** */

/*
 * \brief Open the superblock dealer
 *
 * Prepare the internal data structure of the superblock dealer
 */
void soOpenSBDealerBin();

/* ***************************************** */

/*
 * \brief Close the superblock dealer
 *
 * Save superblock to disk and close dealer
 */
void soCloseSBDealerBin();

/* ***************************************** */

/*
 * \brief Get a pointer to the superblock
 *
 * Load the superblock, if not done yet
 *
 * \return Pointer to superblock
 */
SOSuperBlock* sbGetPointerBin();

/* ***************************************** */

/*
 * \brief Save superblock to disk
 *
 * Do nothing if not loaded
 */
void sbSaveBin();

#endif /*__SOFS17_SBDEALER_BIN___ */
