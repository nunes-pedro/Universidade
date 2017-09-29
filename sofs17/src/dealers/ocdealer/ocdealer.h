/**
 *  \file ocdealer.h
 *
 * \addtogroup dealers
 *
 * @{
 *
 * \defgroup ocdealer ocdealer
 *
 * @{
 *
 * \brief Open-close dealer: start/stop disk dealers
 *
 * \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_OCDEALERS__
#define __SOFS17_OCDEALERS__

/* ***************************************** */

#include <stdint.h>
#include <stdlib.h>

/**
 * \brief call raw level disk openning function and init dealers
 *
 * \param devname path to the file containing the disk
 * \param ntp if not NULL, pointer to the variable where the total number of
 *      blocks of the disk is to be stored
 */
void soOpenDisk(const char *devname, uint32_t * ntp = NULL);

/* ***************************************** */

/**
 * \brief close dealers and call raw level disk closing function
 */
void soCloseDisk();

/* ***************************************** */

/** @} closing group ocdealer */
/** @} closing group dealers */

#endif                          /* __SOFS17_OCDEALERS__ */
