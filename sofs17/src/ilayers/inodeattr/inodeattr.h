/**
 *  \file inodeattr.h
 *
 * \addtogroup ilayers
 *
 * @{
 *
 * \defgroup inodeattr inodeattr 
 *
 * @{
 * 
 *  \brief Functions to manage inode attributes, except cluster references
 *
 *  This module guarantees that only a single copy of every inode is in memory,
 *  thus improving consistency.
 *
 *  \author Artur Pereira - 2016-2017
 */

#ifndef __SOFS17_INODEATTR__
#define __SOFS17_INODEATTR__

#include "probing.h"
#include "itdealer.h"

#include <stdint.h>

/* *************************************************** */

/******************************/
/* lnkcnt attribute */
/******************************/

/**
 * \brief increment, if possible, link count of given inode
 * \param ih inode handler
 * \return link count after operation
 */
uint32_t iIncLnkcnt(int ih);

/**
 * \brief decrement, if possible, link count of given inode
 * \param ih inode handler
 * \return link after operation
 */
uint32_t iDecLnkcnt(int ih);


/**********************************/
/* permission attribute */
/**********************************/

/* ***************************************** */

/**
 * \brief set access permissions of an open inode
 * \param ih inode handler
 * \param perm permissions to be set
 */
void iSetAccess(int ih, uint16_t perm);

/* ***************************************** */

/**
 * \brief retrieve access permissions of an open inode
 * \param ih inode handler
 * \return access permissions
 */
uint16_t iGetAccess(int ih);

/* ***************************************** */

/**
 * \brief check an open inode against a requested access
 * \param ih inode handler
 * \param access requested access
 * \return true, for access granted; false for access denied
 */
bool iCheckAccess(int ih, int access);

/*****************************/
/* time attributes */
/*****************************/

/*****************************/
/* size attributes */
/*****************************/

/* *************************************************** */
/** @} closing group inodeattr */
/** @} closing group ilayers */
/* *************************************************** */

#endif				/* __SOFS17_INODEATTR__ */
