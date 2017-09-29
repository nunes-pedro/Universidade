/**
 *  \brief Definition of the reference bitmap block data type.
 *
 *  \author Artur Pereira - 2017
 *  \author Miguel Oliveira e Silva - 2017
 */

#ifndef __SOFS17_REFBLOCK__
#define __SOFS17_REFBLOCK__

/** \brief reference bytes per free cluster table (bitmap) block */
#define ReferenceBytesPerBitmapBlock (BlockSize - 4)

/** \brief Definition of the reference bitmap block data type. */
struct SORefBlock
{
    /** \brief number of references in block */
    uint16_t cnt;
    /** \brief index of first non-empty byte */
    uint16_t idx;
    /** \brief bit map */
    uint8_t map[ReferenceBytesPerBitmapBlock];
};

#endif				/* __SOFS17_REFBLOCK__ */
