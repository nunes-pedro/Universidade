/**
 *  \file freelists.h
 *
 * \addtogroup ilayers
 *
 * @{
 *
 * \defgroup freelists freelists
 *
 * @{
 *
 * \brief Functions to manage the list of free inodes 
 *      and the list of free clusters
 *
 *  \author Artur Pereira 2008-2009, 2016-2017
 *  \author Miguel Oliveira e Silva 2009, 2017
 *  \author António Rui Borges - 2010-2015
 *
 *  \remarks In case an error occurs, every function throws an SOException
 */

#ifndef __SOFS17_FREELISTS__
#define __SOFS17_FREELISTS__

#include <stdint.h>

/**
 *  \brief Allocate a free inode.
 *
 *  An inode is retrieved from the list of free inodes, marked in use, 
 *  associated to the legal file type passed as
 *  a parameter and is generally initialized. 
 *
 *  \param type the inode type (it must represent either a file, or a directory, or a symbolic link)
 *  \return the number of the allocated inode
 */
uint32_t soAllocInode(uint32_t type);

/**
 *  \brief Free the referenced inode.
 *
 *  The inode is inserted into the list of free inodes.
 *
 *  \param in number of the inode to be freed
 */
void soFreeInode(uint32_t in);

/* *************************************************** */

/**
 *  \brief Allocate a free cluster.
 *
 *  The cluster is retrieved from the retrieval cache of free cluster references. 
 *  If the cache is empty, it has to be replenished before the retrieval may take place.
 *
 *  \return the number of the allocated cluster
 */
uint32_t soAllocCluster();

/* *************************************************** */

/**
 * \brief replenish the retrieval cache
 * \details References to free clusters should be transfered from the free cluster table
 *      (bit map) or insertion cache to the retrieval cache.
 *      Nothing should be done if the retrieval cache is not empty.
 *      The insertion cache should only be used if there are no bits at one in the map.
 *      Only a single block should be processed, even if it is not enough to fulfill the
 *      retrieval cache.
 *      The block to be processes is the one pointed to by the rmidx field of the superblock.
 *      This field should be updated if the processing of the current block reaches its end.
 */
void soReplenish();

/* *************************************************** */

/**
 *  \brief Free the referenced cluster.
 *
 *  \param cn the number of the cluster to be freed
 */
void soFreeCluster(uint32_t cn);

/* *************************************************** */

/**
 * \brief Deplete the insertion cache
 */
void soDeplete();

/* *************************************************** */
/** @} closing group freelists */
/** @} closing group ilayers */
/* *************************************************** */

#endif				/* __SOFS17_FREELISTS__ */
