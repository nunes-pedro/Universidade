/*
 *  \file czdealer.h
 *  \brief clusters dealer: mediates access to the diak cluster zone
 *
 *  This module provides functions to access the cluster zone,
 *  using the logical number of the cluster.
 *
 *  \remarks In case an error occurs, every function throws a SOException
 *
 *  \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_CZDEALER_BIN__
#define __SOFS17_CZDEALER_BIN__

#include <stdint.h>

/* ***************************************** */

/* \brief Open the cluster zone dealer
 *
 * Prepare the internal data structure required by the module
 */
void soOpenCZDealerBin();

/* ***************************************** */

/*
 * \brief Close the cluster zone dealer
 *
 * Clear the internal data structure required by the module
 */
void soCloseCZDealerBin();

/* ***************************************** */

/*
 *  \brief Read a cluster of data from the storage device.
 *
 *  \param n the logical number of the cluster to be read from
 *  \param buf pointer to the buffer where the data must be read into
 */
void soReadClusterBin(uint32_t n, void *buf);

/* ***************************************** */

/*
 *  \brief Write a cluster of data to the storage device.
 *
 *  \param n the logical number of the cluster to be written into
 *  \param buf pointer to the buffer containing the data to be written from
 */
void soWriteClusterBin(uint32_t n, void *buf);

/* ***************************************** */

/*
 * \brief retrieve the maximum number of bytes a file can comprise
 */
uint32_t soGetMaxFileSizeBin();

/* ***************************************** */

#endif            /* __SOFS17_CZDEALER_BIN__ */
