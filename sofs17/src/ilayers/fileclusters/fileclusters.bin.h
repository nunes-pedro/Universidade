/*
 *  \file fileclusters.h
 *  \brief Set of operations to manage file clusters
 *
 *  \author Artur Pereira - 2008-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 *
 *  \remarks In case an error occurs, every function throws an SOException
 */

#ifndef __SOFS17_FILECLUSTER_BIN__
#define __SOFS17_FILECLUSTER_BIN__

#include <stdint.h>

/* *************************************************** */
/* \defgroup filecluster filecluster
 * @{
 */
/* *************************************************** */

/*
 * \brief Get the cluster number of a given file cluster
 *
 *  \param ih inode handler
 *  \param fcn file cluster number
 *  \return the number of the corresponding cluster
 */
uint32_t soGetFileClusterBin(int ih, uint32_t fcn);

/* *************************************************** */

/*
 * \brief Associate a cluster to a given file cluster position
 *
 *  \param ih inode handler
 *  \param fcn file cluster number
 *  \return the number of the allocated cluster
 */
uint32_t soAllocFileClusterBin(int ih, uint32_t fcn);

/* *************************************************** */

/*
 * \brief Free all file clusters from the given position on 
 *
 *  \param ih inode handler
 *  \param ffcn first file cluster number
 */
void soFreeFileClustersBin(int ih, uint32_t ffcn);

/* *************************************************** */

/*
 *  \brief Read a file cluster.
 *
 *  Data is read from a specific data cluster which is supposed to belong 
 *  to an inode associated to a file (a regular
 *  file, a directory or a symbolic link). 
 *
 *  If the referred file cluster has not been allocated yet, 
 *  the returned data will consist of a byte stream filled with the
 *  character null (ascii code 0).
 *
 *  \param ih inode handler
 *  \param fcn file cluster number
 *  \param buf pointer to the buffer where data must be read into
 */
void soReadFileClusterBin(int ih, uint32_t fcn, void *buf);

/* *************************************************** */

/*
 *  \brief Write a data cluster.
 *
 *  Data is written into a specific data cluster which is supposed
 *  to belong to an inode associated to a file (a regular
 *  file, a directory or a symbolic link). 
 *
 *  If the referred cluster has not been allocated yet,
 *  it will be allocated now so that the data can be stored as its
 *  contents.
 *
 *  \param ih inode handler
 *  \param fcn file cluster number
 *  \param buf pointer to the buffer containing data to be written
 */
void soWriteFileClusterBin(int ih, uint32_t fcn, void *buf);

/* *************************************************** */
/* @} */
/* *************************************************** */

#endif             /* __SOFS17_FILECLUSTER_BIN__ */
