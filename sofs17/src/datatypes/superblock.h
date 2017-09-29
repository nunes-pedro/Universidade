/**
 *  \brief Definition of the superblock data type.
 *
 *  \author Artur Pereira - 2008-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#ifndef __SOFS17_SUPERBLOCK__
#define __SOFS17_SUPERBLOCK__

#include <stdint.h>

/** \brief sofs15 magic number */
#define MAGIC_NUMBER 0x50F5

/** \brief sofs15 version number */
#define VERSION_NUMBER 0x2017

/** \brief maximum length of volume name */
#define PARTITION_NAME_SIZE 25

/** \brief size of cache */
#define REFERENCE_CACHE_SIZE  53

/**
 *  \brief Definition of the reference cache data type.
 *
 *  It describes a cache area within the superblock for references to free clusters.
 */
struct SOReferenceCache {
    /** \brief storage area whose elements are logical numbers of free clusters */
    uint32_t ref[REFERENCE_CACHE_SIZE];  ///< the cache area
    uint32_t idx;                        ///< retrieval/insertion point
};

/**
 *  \brief Definition of the superblock data type.
 */
struct SOSuperBlock
{
    /* Header */

    /** \brief magic number - file system identification number */
    uint16_t magic;

    /** \brief version number */
    uint16_t version;

    /** \brief volume name */
    char name[PARTITION_NAME_SIZE + 1];

    /** \brief mount status (1: properly unmounted; 0: otherwise */
    uint8_t mntstat;

    /** \brief number of mounts since last file system check */
    uint8_t mntcnt;

    /** \brief total number of blocks in the device */
    uint32_t ntotal;


    /* Inode table metadata */

    /** \brief physical number of the block where the table of inodes starts */
    uint32_t itstart;

    /** \brief number of blocks that the table of inodes comprises */
    uint32_t itsize;

    /** \brief total number of inodes */
    uint32_t itotal;

    /** \brief number of free inodes */
    uint32_t ifree;

    /** \brief head of linked list of free inodes */
    uint32_t ihead;


    /* Cluster reference map metadata */

    /** \brief physical number of the block where the map of cluster references starts */
    uint32_t rmstart;

    /** \brief number of blocks that the map of cluster references comprises */
    uint32_t rmsize;

    /** \brief index of first byte to be used to retrieve references from map */
    uint32_t rmidx;


    /* Cluster zone metadata */

    /** \brief physical number of the block where the cluster zone starts */
    uint32_t czstart;

    /** \brief total number of clusters */
    uint32_t ctotal;

    /** \brief number of free clusters */
    uint32_t cfree;

    /** \brief retrieval cache of references to free clusters */
    SOReferenceCache rcache;

    /** \brief insert cache of references to free clusters */
    SOReferenceCache icache;
};

#endif /*__SOFS17_SUPERBLOCK__ */
