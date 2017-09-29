/**
 *  \file itdealer.h
 *
 *  \addtogroup dealers
 *
 *  @{
 *
 *  \defgroup itdealer itdealer
 *
 *  @{
 *
 *  \brief inode table dealer: mediates access to the disk inode table
 *      and to the inodes
 *
 *  This module guarantees that only a single copy of every inode is in memory,
 *  thus improving consistency.
 *
 *  \remarks In case an error occurs, every function throws a SOException
 *
 *  \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_ITDEALER__
#define __SOFS17_ITDEALER__

#include "inode.h"

#include <stdint.h>
#include <stdlib.h>

/* ***************************************** */

/** \brief Open inode table dealer
 *
 * Prepare the internal data structure for the inode table dealer
 */
void soOpenITDealer();

/* ***************************************** */

/** 
 * \brief Close the inode table dealer
 *
 * Save to disk all openning inodes and close dealer
 */
void soCloseITDealer();

/* ***************************************** */

/**
 * \brief open inode
 *
 * If inode is already open, just increment usecount;
 * otherwise, transfer the inode from disk and 
 * put usecount at 1.
 *
 * \param in the number of the inode to open
 * \return inode handler
 */
int iOpen(uint32_t in);

/* ***************************************** */

/**
 * \brief Check given handler, throwing an exception in case of error
 * \param ih the handler to be checked
 * \param funcname name of the function making the ckeck
 */
void iCheckHandler(int ih, const char * funcname = NULL);
    
/* ***************************************** */

/**
 * \brief get pointer to an open inode
 *
 * A pointer to the SOInode structured where the inode
 * is loaded is returned.
 *
 * \param ih inode handler
 * \return pointer to the inode
 */
SOInode* iGetPointer(int ih);

/* ***************************************** */

/**
 * \brief Save an open inode to disk
 *
 * The inode is not closed.
 *
 * \param ih inode handler
 */
void iSave(int ih);

/* ***************************************** */

/**
 * \brief Close an open inode
 *
 * Decrement usecount of given inode,
 * releasing slot if 0 is reached.
 *
 * \param ih inode handler
 */
void iClose(int ih);

/* ***************************************** */

/**
 * \brief Return the number of the inode associated to the given handler
 * \param ih inode handler
 * \return inode number
 */
uint32_t iGetInodeNumber(int ih);

/* ***************************************** */

/** @} closing group itdealer */
/** @} closing group dealers */

#endif				/* __SOFS17_ITDEALER__ */
