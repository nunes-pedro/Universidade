/**
 *  \author Artur Pereira - 2007-2009, 2016-2017
 *  \author Miguel Oliveira e Silva - 2009, 2017
 *  \author António Rui Borges - 2010-2015
 */

#include "mksofs.h"

#include "rawdisk.h"
#include "datatypes.h"

#include <stdarg.h>
#include <stdio.h>
#include <libgen.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

/* print help message */
static void printUsage(char *cmd_name)
{
    printf("Sinopsis: %s [OPTIONS] supp-file\n"
           "  OPTIONS:\n"
           "  -n name --- set volume name (default: \"sofs17_disk\")\n"
           "  -i num  --- set number of inodes (default: N/8, where N = number of blocks)\n"
           "  -z      --- set zero mode (default: not zero)\n"
           "  -q      --- set quiet mode (default: not quiet)\n"
           "  -h      --- print this help\n", cmd_name);
}

/* print an INFO message */
static void infoMsg(const char *fmt, ...)
{
    /* print the message */
    fprintf(stdout, "\e[00;34m");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    fprintf(stdout, "\e[0m");
    fflush(stdout);
}

/* print a system error message */
static void errnoMsg(int en, const char *msg)
{
    fprintf(stderr, "\e[00;31m%s: error #%d - %s\e[0m\n", msg, en,
        strerror(en));
}

/* The main function */
int main(int argc, char *argv[])
{
    const char *volname = "sofs17_disk";    /* volume name */
    uint32_t itotal = 0;    /* total number of inodes, if kept, set value automatically */
    bool quiet = false;        /* quiet mode */
    bool zero = false;        /* zero mode */

    /* process command line options */

    int opt;
    while ((opt = getopt(argc, argv, "n:i:qzh")) != -1)
    {
        switch (opt)
        {
            case 'n':    /* volume name */
            {
                volname = optarg;
                break;
            }
            case 'i':    /* total number of inodes */
            {
                uint32_t n = 0;
                sscanf(optarg, "%u%n", &itotal, &n);
                if (n != strlen(optarg))
                {
                    fprintf(stderr, "%s: Wrong number of inodes value.\n", basename(argv[0]));
                    printUsage(basename(argv[0]));
                    return EXIT_FAILURE;
                }
                break;
            }
            case 'q':    /* quiet mode */
            {
                quiet = true;
                break;
            }
            case 'z':    /* zero mode */
            {
                zero = true;    
                break;
            }
            case 'h':    /* help mode */
            {
                printUsage(basename(argv[0]));
                return EXIT_SUCCESS;
            }
            default:
            {
                fprintf(stderr, "%s: Wrong option.\n", basename(argv[0]));
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
    const char *devname = argv[optind];

    try
    {
        /* open the storage device */
        uint32_t ntotal;
        soOpenRawDisk(devname, &ntotal);

        /* if itotal not set, apply default value */
        if (itotal == 0)
            itotal = ntotal / 8;

        if (!quiet) 
            infoMsg("Trying to install a %ld-inodes SOFS17 file system in %s.\n", 
                    itotal, argv[optind]);

        /* compute structural division of the disk */
        uint32_t itsize; // number of blocks used by inode table
        uint32_t rmsize; // number of blocks used by cluster reference table
        uint32_t ctotal; // number of clusters
        if (!quiet) infoMsg("  Computing disk structure... ");
        computeStructure(ntotal, itotal, &itsize, &rmsize, &ctotal);
        if (!quiet) infoMsg("done.\n");

        /* filling in the superblock fields: */
        if (!quiet) infoMsg("  Filling in the superblock fields... ");
        fillInSuperBlock(volname, ntotal, itsize, rmsize);
        if (!quiet) infoMsg("done.\n");

        /* filling in the inode table: */
        if (!quiet) infoMsg("  Filling in the table of inodes... ");
        fillInInodeTable(1, itsize);
        if (!quiet) infoMsg("done.\n");

        /* fill in the table/bit map of references to free cluster */
        if (!quiet) infoMsg("  Filling in the bitmap of free clusters... ");
        fillInFreeClusterTable(1 + itsize, ctotal);
        if (!quiet) infoMsg("done.\n");

        /* filling in the root directory: */
        if (!quiet) infoMsg("  Filling in the root directory... ");
        fillInRootDir(1 + itsize + rmsize);
        if (!quiet) infoMsg("done.\n");

        /* reset free cluster, if required */
        if (zero)
        {
            if (!quiet) infoMsg("  Filling in free clusters with zeros... ");
            resetClusters(1 + itsize + rmsize + BlocksPerCluster, ctotal - 1);
            if (!quiet) infoMsg("done\n");
        }

        /* set magic number and save superblock */
        SOSuperBlock sb;
        soReadRawBlock(0, &sb);
        sb.magic = MAGIC_NUMBER;
        soWriteRawBlock(0, &sb);

        /* close device and quit */
        soCloseRawDisk();
        if (!quiet) 
            infoMsg("A %ld-inodes SOFS17 file system was successfully installed in %s.\n", 
                        sb.itotal, argv[optind]);
    }
    catch (int err)
    {
        errnoMsg(err, "Fail formating disk");
        return EXIT_FAILURE;
    }
    
    /* that's all */
    return EXIT_SUCCESS;
}    /* end of main */

