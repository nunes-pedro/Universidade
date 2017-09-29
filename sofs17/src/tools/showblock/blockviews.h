/**
 *  \file blockviews.h
 *
 *  \brief Display the contents of a block as:
 *
 *      \li hexadecimal data
 *      \li ascii data
 *      \li superblock data
 *      \li inode data
 *      \li cluster references
 *      \li directory entry.
 *
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#ifndef __SOFS17_BLOCKVIEWS__
#define __SOFS17_BLOCKVIEWS__

#include <stdint.h>

#include "datatypes.h"

/**
 *  \brief Display block as hexadecimal data.
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockAsHex(void *buf, uint32_t off = 0x0);

/**
 *  \brief Display cluster as ASCII data.
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockAsAscii(void *buf, uint32_t off = 0x0);

/**
 *  \brief Display the block contents as superblock data.
 *
 *  \param buf pointer to a buffer with block contents
 */
void printSuperBlock(void* buf);

/**
 *  \brief Display the inode data.
 *
 *  \param buf pointer to a buffer with inode contents
 *  \param nInode inode number
 */
void printInode(void* buf, uint32_t nInode);

/**
 *  \brief Display the block contents as inode data.
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockOfInodes(void *buf, uint32_t off = 0x0);

/**
 *  \brief Display the block contents as direntry data.
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockOfDirents(void *buf, uint32_t off = 0x0);

/**
 *  \brief Display the block contents as reference data.
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockOfRefs(void *buf, uint32_t off = 0x0);

/**
 *  \brief Display the block contents as block of free cluster table (bitmap).
 *
 *  \param buf pointer to a buffer with block contents
 *  \param off offset for the labels
 */
void printBlockAsBitmapRefs(void *buf, uint32_t off = 0x0);

#endif				/* __SOFS17_BLOCKVIEWS__ */
