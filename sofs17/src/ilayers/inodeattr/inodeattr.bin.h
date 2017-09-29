/*
 *  \file inodeattr.h
 *  \brief manage inode attributes, except cluster references
 *
 *  This module guarantees that only a single copy of every inode is in memory,
 *  thus improving consistency.
 *
 *  \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_INODEATTR_BIN__
#define __SOFS17_INODEATTR_BIN__

#include "probing.h"
#include "itdealer.h"

#include <stdint.h>

/* *************************************************** */
/* \defgroup inodeattr inodeattr @{ */
/* *************************************************** */

/******************************/
/* lnkcnt attribute */
/******************************/

/*
 * \brief increment, if possible, link count of given inode
 * \param ih inode handler
 * \return link count after operation
 */
uint32_t iIncLnkcntBin(int ih);

/*
 * \brief decrement, if possible, link count of given inode
 * \param ih inode handler
 * \return link after operation
 */
uint32_t iDecLnkcntBin(int ih);


/**********************************/
/* permission attribute */
/**********************************/

/* ***************************************** */

/*
 * \brief set access permissions of an open inode
 * \param ih inode handler
 * \param perm permissions to be set
 */
void iSetAccessBin(int ih, uint16_t perm);

/* ***************************************** */

/*
 * \brief retrieve access permissions of an open inode
 * \param ih inode handler
 * \return access permissions
 */
uint16_t iGetAccessBin(int ih);

/* ***************************************** */

/*
 * \brief check an open inode against a requested access
 * \param ih inode handler
 * \param access requested access
 * \return true, for access granted; false for access denied
 */
bool iCheckAccessBin(int ih, int access);

/*****************************/
/* time attributes */
/*****************************/

/*****************************/
/* size attributes */
/*****************************/

/* *************************************************** */
/* @} */
/* *************************************************** */

#endif				/* __SOFS17_INODEATTR_BIN__ */
