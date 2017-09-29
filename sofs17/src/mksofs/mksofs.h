/**
 * \file mksofs.h
 *
 * \addtogroup rawlevel 
 *
 * @{
 *
 * \defgroup mksofs mksofs
 *
 * \brief Formatting functions
 *
 * @{
 *
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#ifndef __SOFS17_MKSOFS__
#define __SOFS17_MKSOFS__

#include "datatypes.h"

/**
 * \brief computes the structural division of the disk
 * \details The structural division is computed, possible adjusting the number of 
 *      inodes in order to use the whole disk.
 *      If the given number of inodes is zero, a default value,
 *      equal to the number of blocks divided by 8, is used.
 * \param ntotal total number of blocks of the device
 * \param itotal requested number of inodes
 * \param itsizep pointer to mem where to store the size of inode table in blocks
 * \param rmsizep pointer to mem where to store the size of cluster reference table in blocks
 * \param ctotalp pointer to mem where to store the number of clusters
 */
void computeStructure(uint32_t ntotal, uint32_t itotal,
            uint32_t * itsizep, uint32_t * rmsizep, uint32_t * ctotalp);


/**
 * \brief Fill in the fields of the superblock.
 * \details The magic number should be put at 0xFFFF.
 * \param name volume name
 * \param ntotal the total number of blocks in the device
 * \param itsize the number of blocks used by the inode table
 * \param rmsize the number of blocks used by the cluster reference table
 */
void fillInSuperBlock(const char *name, uint32_t ntotal, uint32_t itsize, uint32_t rmsize);


/**
 * \brief Fill in the blocks of the inode table.
 * \details The inode 0 must be filled assuming it is used by the root directory.
 *      The other inodes are free
 * \param itstart physical number of the first block used by the inode table
 * \param itsize number of blocks of the inode table
 */
void fillInInodeTable(uint32_t itstart, uint32_t itsize);


/**
 * \brief Fill in the blocks of the free cluster table
 * \details There is a one to one correspondence between bits in the table and clusters.
 *      Bits on the table are considered to grow up from lower blocks to upper blocks, from 
 *      lower bytes to upper bytes, and from most significant bits (MSB) 
 *      to least significant bits (LSB).
 *      Thus, bit 0 corresponds to the most significant bit of the first byte of first block
 *      of the table.
 *      A bit at 1 means the corresponding cluster is free. Conversely, a bit at 0 means the
 *      corresponding cluster is in use.
 *      Bit 0, as the root occupies the first cluster, must be set in use.
 *      The number of bits in the table is, in general, greater than the number of clusters.
 *      The non used bits should be put as in use.
 * \param rmstart the number of the fisrt block used by the bit table
 * \param ctotal the total number of clusters
 */
void fillInFreeClusterTable(uint32_t rmstart, uint32_t ctotal);


/** 
 * \brief Fill in the root directory
 * \details The root directory occupies one cluster, with the first two slots filled in with
 *      "." and ".." directory entries.
 *      The other slots must be cleaned: field \c name filled with zeros and field \c inode
 *      filled with \c NullReference.
 * \param rtstart number of the block where the root cluster starts.
 */
void fillInRootDir(uint32_t rtstart);


/**
 * \brief Fill with zeros the given set of clusters
 * \param cstart number of the block of the first free cluster
 * \param ctotal number of clusters to be filled
 */
void resetClusters(uint32_t cstart, uint32_t ctotal);

/* ***************************************** */

/** @} closing group mksofs */
/** @} closing group rawlevel */

#endif   /* __SOFS17_MKSOFS__ */
