/**
 *  \brief Definition of the directory entry data type.
 *
 *  \author Artur Pereira - 2008-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#ifndef __SOFS17_DIRENTRY__
#define __SOFS17_DIRENTRY__

/** \brief maximum length of a file name (in characters) */
#define SOFS17_MAX_NAME 59

/** \brief Definition of the directory entry data type. */
struct SODirEntry
{
    /** \brief the associated inode number */
    uint32_t in;
    /** \brief the name of a file (NULL-terminated string) */
    char name[SOFS17_MAX_NAME + 1];
};

#endif				/* __SOFS17_DIRENTRY__ */
