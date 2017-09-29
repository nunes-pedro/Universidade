/*
 *  \author Artur Pereira - 2006-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "rawdisk.h"
#include "datatypes.h"
#include "blockviews.h"

/*
 * print help message
 */
static void printUsage(char *cmd_name)
{
    printf("Sinopsis: %s [ OPTION ] supp-file\n"
           "  OPTIONS:\n"
           "  -x range   --- show block(s) as hexadecimal data\n"
           "  -a range   --- show block(s) as ascii/hexadecimal data\n"
           "  -s range   --- show block(s) as superblock data\n"
           "  -i range   --- show block(s) as inode entries\n"
           "  -d range   --- show block(s) as directory entries\n"
           "  -r range   --- show block(s) as cluster references\n"
           "  -b range   --- show block(s) as bitmap references\n"
           "  -h         --- print this help\n", cmd_name);
}

/* print error message */
static void printError(int errcode, char *cmd_name)
{
    fprintf(stderr, "%s: error #%d - %s.\n", cmd_name, errcode,
        strerror(errcode));
}

/* The main function */

int main(int argc, char *argv[])
{
    /* process command line options */
    int opt;
    int sopt = '_';
    const char* range = "0";

    while ((opt = getopt(argc, argv, "x:a:s:i:d:r:b:h")) != -1)
    {
        switch (opt) 
        {
            case 'x':        /* show block contents as hexadecimal data */
            case 'a':        /* show block contents as ascii data */
            case 's':        /* show block contents as superblock data */
            case 'i':        /* show block contents as inode entries */
            case 'd':        /* show block contents as directory entries */
            case 'r':        /* show block contents as cluster references */
            case 'b':        /* show block contents as bitmap references */
            {
                if (sopt != '_')
                {
                    fprintf(stderr, "%s: Too many options.\n", basename(argv[0]));
                    printUsage(basename(argv[0]));
                    return EXIT_FAILURE;
                }   
                range = optarg;
                sopt = opt;
                break;
            }
            case 'h':
            {
                printUsage(basename(argv[0]));
                return EXIT_SUCCESS;
            }
            default:
            {
                fprintf(stderr, "%s: It should not have happened.\n", basename(argv[0]));
                printUsage(basename(argv[0]));
                return EXIT_FAILURE;
            }
        }
    }

    /* check existence of mandatory argument: storage device name */
    if ((argc - optind) != 1) 
    {
        fprintf(stderr, "%s: Wrong number of mandatory arguments.\n", basename(argv[0]));
        printUsage(basename(argv[0]));
        return EXIT_FAILURE;
    }

    /* if no selected option is given, assume '-s 0' */
    if (sopt == '_')
        sopt = 's';

    /* open a direct communication channel with the storage device */
    uint32_t nb;
    try
    {
        soOpenRawDisk(argv[optind], &nb);
    }
    catch (int err)
    {
        printError(err, basename(argv[0]));
        return EXIT_FAILURE;
    }

    /* check range */
    uint32_t i1 = 0, i2 = 0;
    unsigned int n1 = 0, n2 = 0;
    sscanf(range, "%u%n-%u%n", &i1, &n1, &i2, &n2);
    if (n1 == strlen(range))
    {
        i2 = i1;
    }
    else if (n2 != strlen(range) || i2 < i1 || i2 >= nb)
    {
        fprintf(stderr, "%s: Wrong range format.\n", basename(argv[0]));
        printUsage(basename(argv[0]));
        return EXIT_FAILURE;
    }

    /* process request */
    char buf[BlockSize];
    uint32_t off = 0;
    for (uint32_t i = i1; i <= i2; i++)
    {
        try
        {
            soReadRawBlock(i, buf);
        }
        catch (int err)
        {
            printError(err, basename(argv[0]));
            return EXIT_FAILURE;
        }
        switch(sopt)
        {
            case 'x':
                printBlockAsHex(buf, off);
                off += BlockSize;
                break;
            case 'a':
                printBlockAsAscii(buf, off);
                off += BlockSize;
                break;
            case 'i':
                printBlockOfInodes(buf, off);
                off += InodesPerBlock;
                break;
            case 'd':
                printBlockOfDirents(buf, off);
                off += DirentriesPerCluster / BlocksPerCluster;
                break;
            case 'r':
                printBlockOfRefs(buf, off);
                off += ReferencesPerBlock;
                break;
            case 'b':
                printBlockAsBitmapRefs(buf, off);
                off += ReferencesPerBitmapBlock;
                break;
            case 's':
                printSuperBlock(buf);
                break;
        }
    }

    /* close the communication channel with the storage device */
    try
    {
        soCloseRawDisk();
    }
    catch (int err)
    {
        printError(err, basename(argv[0]));
        return EXIT_FAILURE;
    }

    /* that's all */
    return EXIT_SUCCESS;

}                /* end of main */

