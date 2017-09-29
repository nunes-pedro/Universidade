/*
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2012
 */

#define  __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

#include "rawdisk.h"
#include "datatypes.h"

/* ********************************************************* */

void printBlockAsHex(void *buf, uint32_t off)
{
    /* cast buf to appropriated type */
    unsigned char* byte = (unsigned char *)buf;

    /* print cluster */
    for (uint32_t i = 0; i < BlockSize; i++) 
    {
        if ((i & 0x1f) == 0)
            printf("%4.4x:", i+off);
        /* print byte */
        printf(" %.2x", byte[i]);
        /* terminate present line, if required */
        if ((i & 0x1f) == 0x1f)
            printf("\n");
    }
}

/* ********************************************************* */

void printBlockAsAscii(void *buf, uint32_t off)
{
    /* cast buf to appropriated type */
    unsigned char* c = (unsigned char *)buf;

    /* print cluster */
    char line[256];        /* line to be printed */
    char *p_line = line;    /* pointer to a character in the line */
    for (uint32_t i = 0; i < BlockSize; i++) 
    {
        if ((i & 0x1f) == 0) {
            printf("%4.4d:", i+off);
            p_line = line;
        }
        /* add character to the line */
        switch (c[i]) {
        case '\a':
            p_line += sprintf(p_line, " \\a");
            break;
        case '\b':
            p_line += sprintf(p_line, " \\b");
            break;
        case '\f':
            p_line += sprintf(p_line, " \\f");
            break;
        case '\n':
            p_line += sprintf(p_line, " \\n");
            break;
        case '\r':
            p_line += sprintf(p_line, " \\r");
            break;
        case '\t':
            p_line += sprintf(p_line, " \\t");
            break;
        case '\v':
            p_line += sprintf(p_line, " \\v");
            break;
        default:
            if ((c[i] >= ' ') && (c[i] != 0x7F) && (c[i] != 0x8F))
                p_line += sprintf(p_line, " %c ", c[i]);
            else
                p_line += sprintf(p_line, " %.2x", c[i]);
        }
        /* terminate and print present line, if required */
        if ((i & 0x1f) == 0x1f) {
            *p_line = '\0';
            printf("%s\n", line);
        }
    }
}

/* ********************************************************* */

void printSuperBlock(void *buf)
{
    /* cast buf to appropriated type */
    SOSuperBlock* sbp = (SOSuperBlock *) buf;

    /* header */
    printf("Header:\n");
    printf("   Magic number: 0x%0"PRIX16"\n", sbp->magic);
    printf("   Version number: 0x%0"PRIX16"\n", sbp->version);
    printf("   Volume name: %-s\n", sbp->name);
    printf("   Properly unmounted: %s\n", (sbp->mntstat == 1) ? "yes" : "no");
    printf("   Number of mounts: %" PRIu8 "\n", sbp->mntcnt);
    printf("   Total number of blocks in the device: %"PRIu32"\n", sbp->ntotal);

    /* inode table metadata */
    printf("Inode table metadata:\n");
    printf("   First block of the inode table: %u\n", sbp->itstart);
    printf("   Number of blocks of the inode table: %u\n", sbp->itsize);
    printf("   Total number of inodes: %u\n", sbp->itotal);
    printf("   Number of free inodes: %u\n", sbp->ifree);
    printf("   Head of list of free inodes: ");
    if (sbp->ihead == NullReference) 
        printf("(nil)\n");
    else
        printf("%" PRIu32 "\n", sbp->ihead);

    /* reference metadata */
    printf("Free cluster table metadata:\n");
    printf("   First block of the free cluster table: %u\n", sbp->rmstart);
    printf("   Number of blocks of the free cluster table: %u\n", sbp->rmsize);
    printf("   Index of first byte to retrieve references: %u\n", sbp->rmidx);

    /* clusters metadata */
    printf("Clusters metadata:\n");
    printf("   First block of the cluster zone: %u\n", sbp->czstart);
    printf("   Total number of clusters: %u\n", sbp->ctotal);
    printf("   Number of free clusters: %u\n", sbp->cfree);
    printf("   Retrieval cache:\n");
    printf("      Index of the first filled cache element: ");
    if (sbp->rcache.idx == REFERENCE_CACHE_SIZE)
        printf(" (nil)\n");
    else
        printf(" %u\n", sbp->rcache.idx);
    printf("      Cache contents:\n");
    printf("        ");
    for (uint32_t i = 0; i < REFERENCE_CACHE_SIZE; i++)
    {
        if (sbp->rcache.ref[i] == NullReference)
            printf(" (nil)");
        else
            printf(" %u", sbp->rcache.ref[i]);

        /* change line at every 10 elements */
        if (i % 10 == 9)
        {
            printf("\n");
            printf("        ");
        }
    }
    printf("\n");
    printf("   Insertion cache:\n");
    printf("      Index of the first free cache element: ");
    if (sbp->icache.idx == REFERENCE_CACHE_SIZE)
        printf(" (nil)\n");
    else
        printf(" %u\n", sbp->icache.idx);
    printf("      Cache contents:\n");
    printf("        ");
    for (uint32_t i = 0; i < REFERENCE_CACHE_SIZE; i++)
    {
        if (sbp->icache.ref[i] == NullReference)
            printf(" (nil)");
        else
            printf(" %u", sbp->icache.ref[i]);
        /* change line at every 10 elements */
        if ((i % 10) == 9 )
        {
            printf("\n");
            printf("        ");
        }
    }
    printf("\n");
}

/* ********************************************************* */

/** \brief Bit pattern description of the mode field in the inode data type */
static const char *inodetypes[] = { 
    "clean",
    "INVALID_001",
    "INVALID-002",
    "INVALID_003",
    "directory",
    "INVALID-005",
    "INVALID-006",
    "INVALID_007",
    "regular file",
    "INVALID_011",
    "symlink",
    "INVALID_013",
    "INVALID-014",
    "INVALID-015",
    "INVALID-016"
    "INVALID-017"
};

void printInode(void* buf, uint32_t in)
{
    SOInode* ip = (SOInode*)buf;

    /* print inode number */
    printf("Inode #");
    if (in == NullReference)
        printf("(nil)\n");
    else
        printf("%u\n", in);

    /* decouple and print mode field */
    bool not_in_use = (ip->mode & INODE_FREE) == INODE_FREE;
    uint32_t typebits = (ip->mode & S_IFMT) >> 12;
    printf("type = %s%s, ", not_in_use ? "free " : " ", inodetypes[typebits]);

    uint32_t permbits = ip->mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    char perm[10] = "rwxrwxrwx";    /* access permissions array */
    for (int i = 0; i < 9; i++)
    {
        if ((permbits % 2) == 0) // LSB is zero ?
        {
            perm[8-i] = '-';
        }
        permbits >>= 1;
    }
    printf("permissions = %s, ", perm);

    /* print reference count */
    printf("lnkcnt = %"PRIu16", ", ip->lnkcnt);

    /* print owner and group IDs */
    printf("owner = %"PRIu32", group = %"PRIu32"\n", ip->owner, ip->group);

    /* print file size in bytes and in clusters */
    printf("size in bytes = %"PRIu32", size in clusters = %"PRIu32"\n",
           ip->size, ip->clucnt);

    /* decouple and print information about dates of file manipulation, 
     * if inode is in use, or about the inode references
     * within the double-linked list that holds the free inodes */
    if (not_in_use)
    {
        printf("next = ");
        if (ip->next == NullReference)
            printf("(nil), ");
        else
            printf("%"PRIu32", ", ip->next);
        printf(", prev = ");
        if (ip->prev == NullReference)
            printf("(nil)\n");
        else
            printf("%"PRIu32"\n", ip->prev);
    }
    else    /* inode is in use */
    {    
        char timebuf[30];
        time_t t = ip->atime;
        ctime_r(&t, timebuf);
        timebuf[strlen(timebuf) - 1] = '\0';
        printf("atime = %s, ", timebuf);
        t = ip->mtime;
        ctime_r(&t, timebuf);
        timebuf[strlen(timebuf) - 1] = '\0';
        printf("mtime = %s, ", timebuf);
        t = ip->ctime;
        ctime_r(&t, timebuf);
        timebuf[strlen(timebuf) - 1] = '\0';
        printf("ctime = %s\n", timebuf);
    }

    /* print direct references */
    printf("d[] = {");
    for (int i = 0; i < N_DIRECT; i++) {
        if (i > 0)
            printf(" ");
        if (ip->d[i] == NullReference)
            printf("(nil)");
        else
            printf("%" PRIu32 "", ip->d[i]);
    }
    printf("}, ");
    
    /* print single indirect references */
    printf("i1 = ");
    if (ip->i1 == NullReference)
        printf("(nil)");
    else
        printf("%" PRIu32, ip->i1);

    /* print double indirect reference */
    printf(", i2 = ");
    if (ip->i2 == NullReference)
        printf("(nil)\n");
    else
        printf("%" PRIu32 "\n", ip->i2);

    printf("----------------\n");
}

/* ********************************************************* */

void printBlockOfInodes(void *buf, uint32_t off)
{
    /* cast buf to appropriated type */
    SOInode* inode = (SOInode *)buf;

    /* treat each inode stored in the block separately */
    for (uint32_t i = 0; i < InodesPerBlock; i++)
        printInode(&inode[i], i+off);
}

/* ********************************************************* */

void printBlockOfDirents(void *buf, uint32_t off)
{
    /* get dirents per cluster */
    uint32_t dpb = BlockSize / sizeof(SODirEntry);

    /* cast buf to appropriated type */
    SODirEntry* dir = (SODirEntry*)buf;

    /* print */
    for (uint32_t i = 0; i < dpb; i++)
    {
        printf("%-*.*s ", SOFS17_MAX_NAME, SOFS17_MAX_NAME, dir[i].name);
        if (dir[i].in == NullReference)
            printf("(nil)\n");
        else
            printf("%.10"PRIu32"\n", dir[i].in);
    }
}

/* ********************************************************* */

void printBlockOfRefs(void *buf, uint32_t off)
{
    /* get refs per block */
    uint32_t rpb = BlockSize / sizeof(uint32_t);

    /* cast buf to appropriated type */
    uint32_t* ref = (uint32_t*)buf;

    for (uint32_t i = 0; i < rpb; i++)
    {
        if ((i & 0x07) == 0)
            printf("%4.4d:", i+off);
        /* print reference to a cluster */
        if (ref[i] == NullReference)
            printf("   (nil)   ");
        else
            printf(" %.10"PRIu32, ref[i]);
        /* terminate present line, if required */
        if (((i & 0x07) == 0x07) || (i == (rpb - 1)))
            printf("\n");
    }
}

/* ********************************************************* */

void printBlockAsBitmapRefs(void *buf, uint32_t off = 0x0)
{
    /* cast buf to appropriated type */
    SORefBlock* rblk = (SORefBlock*)buf;

    /* print count and index */
    printf("cnt = %"PRIu16", ", rblk->cnt);
    printf("idx = %"PRIu16"\n", rblk->idx);

    /* print bits */
    for (uint32_t i = 0; i < ReferenceBytesPerBitmapBlock; i++) 
    {
        if ((i & 0x1f) == 0)
            printf("%4.4x:", i+off);
        /* print byte */
        printf(" %.2x", rblk->map[i]);
        /* terminate present line, if required */
        if ((i & 0x1f) == 0x1f)
            printf("\n");
    }
    printf("\n");
}

/* ********************************************************* */
