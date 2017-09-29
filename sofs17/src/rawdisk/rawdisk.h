/**
 *  \file rawdisk.h
 *
 * \defgroup rawlevel rawlevel
 *
 * \brief Manipulation of the disk at block level
 *
 * @{
 *
 * \defgroup rawdisk rawdisk
 *
 * @{
 *
 * \brief Access to disk blocks at raw level
 *
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 *
 *  \remarks In case an error occurs, every function throws an error code (an int)
 */

#ifndef __SOFS17_RAWDISK__
#define __SOFS17_RAWDISK__

#include <stdint.h>
#include <stdlib.h>

/* ***************************************** */

/** \brief block size (in bytes) */
#define BlockSize (512U)

/* ***************************************** */

/**
 *  \brief Open the storage device.
 *
 *  A communication channel is established with the storage device.
 *  It is supposed that no communication channel was previously established.
 *  The storage file must exist and have a size multiple of the block size.
 *
 *  \param devname absolute path to the Linux file that simulates the storage device
 *  \param np if not null,
 *      pointer to a location where the number of blocks of the device is to be stored
 *
 */
void soOpenRawDisk(const char *devname, uint32_t * np = NULL);

/* ***************************************** */

/**
 *  \brief Close the storage device.
 *
 *  The communication channel previously established with the storage device is closed.
 */
void soCloseRawDisk(void);

/* ***************************************** */

/**
 *  \brief Read a block of data from the storage device.
 *
 *  \param n physical number of the data block to be read from
 *  \param buf pointer to the buffer where the data must be read into
 */
void soReadRawBlock(uint32_t n, void *buf);

/* ***************************************** */

/**
 *  \brief Write a block of data from the storage device.
 *
 *  \param n physical number of the block to be written into
 *  \param buf pointer to the buffer containing the data to be written from
 */
void soWriteRawBlock(uint32_t n, void *buf);

/* ***************************************** */

/** @} closing group rawdisk */
/** @} closing group rawlevel */

#endif				/* __SOFS17_RAWDISK__ */
