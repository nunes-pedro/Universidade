/**
 *  \brief A test tool
 *  
 *  It provides a simple method to test separately the file system internal operations.
 *
 *  \author Artur Pereira - 2005-2009, 2016-2017
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
#include <time.h>
#include <errno.h>
#include <stdarg.h>

#include "probing.h"
#include "exception.h"
#include "rawdisk.h"
#include "datatypes.h"
#include "ocdealer.h"
#include "itdealer.h"
#include "freelists.h"
#include "fileclusters.h"
#include "direntries.h"
#include "blockviews.h"

/* quiet level 
 * 0 - print all messages
 * 1 - print only result messages
 * 2 - print nothing 
 */
static int quiet = 0;

/* Log stream id */
static FILE* flog = stdout;        /* log stream default */
static FILE* fin = stdin;       /* input stream */
static const char* devname = NULL;

static char *progName = NULL;   /* this program's basename */
static char *progDir = NULL;    /* this program's directory */

static int lowerProbe = 0;
static int upperProbe = 999;

/* ******************************************** */
/* print help message */
static void printUsage(char *cmd_name)
{
    if (quiet > 0)
        return;

    printf("Sinopsis: %s [OPTIONS] supp-file\n"
           "  OPTIONS:\n"
           "  -q level --- set quiet mode (default: 0)\n"
           "  -l depth --- set log depth (default: 0,0)\n"
           "  -h       --- print this help\n", cmd_name);
}

/* ******************************************** */
/* print a prompt message */
static void promptMsg(const char *fmt, ...)
{
    if (quiet > 0)
        return;

    /* print the message */
    //fprintf(stdout, "\e[01;34m");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    //fprintf(stdout, "\e[0m");
    fflush(stdout);
}

/* ******************************************** */
/* print a result message */
static void resultMsg(const char *fmt, ...)
{
    if (quiet > 1)
        return;

    /* print the message */
    //fprintf(stdout, "\e[01;34m");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    //fprintf(stdout, "\e[0m");
    fflush(stdout);
}

/* ******************************************** */
/* print an ERROR message */
static void errorMsg(const char *fmt, ...)
{
    if (quiet > 1)
        return;

    /* print the message */
    fprintf(stderr, "\e[01;31m");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\e[0m\n");
}

/* ******************************************** */
/* print an ERRNO message */
static void errnoMsg(int en, const char *fmt, ...)
{
    if (quiet > 1)
        return;

    /* print the message */
    fprintf(stderr, "\e[01;31m");
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, ": %s (%d).\e[0m\n", strerror(en), en);
}

/* ******************************************** */
/* purge remainder of line */
static void fPurge(FILE* fin)
{
    //return;
    fscanf(fin, "%*[^\n]");
    fscanf(fin, "%*c");
}

/* ******************************************** */
/* not used */
//static void notUsed(void)
//{
//    fprintf(stderr, "\e[02;41m==>\e[0m ");
//    fprintf(stderr, "Option not used. Try another\n");
//}

/* ******************************************** */
/* still not implemented */
static void notImplemented(void)
{
    fprintf(stderr, "\e[02;41m==>\e[0m ");
    fprintf(stderr, "Option still not implemented.\n");
}

/* ******************************************** */
/* set probe depths */
static void setProbeDepths(void)
{
    /* ask for lower depth */
    promptMsg("Lower depth: ");
    int n1;
    fscanf(fin, "%d", &n1);
    fPurge(fin);
    if (n1 < 0)
    {
        errorMsg("Wrong number: %d", n1);
        return;
    }

    /* ask for upper depth */
    promptMsg("Upper depth: ");
    int n2;
    fscanf(fin, "%d", &n2);
    fPurge(fin);
    if (n2 < 0)
    {
        errorMsg("Wrong number: %d", n2);
        return;
    }
    
    if (n1 > n2)
    {
        errorMsg("Upper depth can not be less than the lower one");
        return;
    }

    lowerProbe = n1;
    upperProbe = n2;

    /* activate new depths */
    soSetProbeDepths(n1, n2);
}

/* ******************************************** */
/* create disk */
static void createDisk(void)
{
    notImplemented();
    return;

    /* ask for number of blocks */
    promptMsg("Number of blocks: ");
    int n;
    fscanf(fin, "%d", &n);
    fPurge(fin);
    if (n < 3)
    {
        errorMsg("Wrong number: %d", n);
        return;
    }

    /* create disk */
}

/* ******************************************** */
/* format disk */
static void formatDisk(void)
{
    /* ask for number of inodes */
    promptMsg("Number of inodes: ");
    int n;
    fscanf(fin, "%d", &n);
    fPurge(fin);
    if (n < 0)
    {
        errorMsg("Wrong number: %d", n);
        return;
    }

    /* close disk */
    try
    {
        soCloseDisk();
    }
    catch(SOException & err)
    {
        errnoMsg(err.en, err.msg);
        exit(EXIT_FAILURE);
    }

    /* format disk */
    char cmd[1000];
    sprintf(cmd, "%s/mksofs %s -i %d", progDir, devname, n);
    system(cmd);

    /* reopen disk */
    try
    {
        soOpenDisk(devname);
    }
    catch(SOException & err)
    {
        errnoMsg(err.en, err.msg);
        exit(EXIT_FAILURE);
    }

    /* wait for ENTER */
    promptMsg("Press ENTER to continue");
    fscanf(fin, "%*[^\n]");
    fPurge(fin);
}

/* ******************************************** */
/* show block */
static void showBlock(void)
{
    /* ask for format */
    promptMsg("Display format (s, i, r, d, x, a, b): ");
    char t;
    fscanf(fin, "%c", &t);
    fPurge(fin);
    if (strchr("sirdxab", t) == NULL)
    {
        errorMsg("Wrong format\n");
        return;
    }

    /* ask for range */
    char range[100];
    promptMsg("block range: ");
    fscanf(fin, "%s", range);
    fPurge(fin);

    /* call showblock */
    char cmd[1000];
    sprintf(cmd, "%s/showblock %s -%c %s", 
                progDir, devname, t, range);
    system(cmd);

    /* wait for ENTER */
    promptMsg("Press ENTER to continue");
    fscanf(fin, "%*[^\n]");
    fPurge(fin);
}

/* ******************************************** */
/* alloc inode */
static uint32_t iType[] = { S_IFREG, S_IFDIR, S_IFLNK };

static void allocInode(void)
{
    /* ask for type */
    promptMsg("Inode type (1 - file, 2 - dir, 3 - symlink): ");
    int t;
    fscanf(fin, "%d", &t);
    fPurge(fin);
    if (t < 1 || t > 3)
    {
        errorMsg("Wrong type: %d", t);
        return;
    }

    /* call function */
    uint32_t in = soAllocInode(iType[t-1]);

    /* print result */
    resultMsg("Inode number %u allocated\n", in);
}

/* ******************************************** */
/* free inode */
static void freeInode(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* call function */
    soFreeInode(in);

    /* print result */
    resultMsg("Inode number %u freed\n", in);
}

/* ******************************************** */
/* alloc data cluster */
static void allocCluster(void)
{
    /* call function */
    uint32_t cn = soAllocCluster();

    /* print result */
    resultMsg("Cluster number %u allocated\n", cn);
}

/* ******************************************** */
/* replenish */
static void replenish(void)
{
    /* call function */
    soReplenish();

    /* print result */
    resultMsg("replenish done\n");
}

/* ******************************************** */
/* free file cluster */
static void freeCluster(void)
{
    /* ask for cluster number */
    promptMsg("Cluster number: ");
    uint32_t cn;
    fscanf(fin, "%u", &cn);
    fPurge(fin);

    /* call function */
    soFreeCluster(cn);

    /* print result */
    resultMsg("Cluster number %u freed\n", cn);
}

/* ******************************************** */
/* deplete */
static void deplete(void)
{
    /* call function */
    soDeplete();

    /* print result */
    resultMsg("deplete done\n");
}

/* ******************************************** */
/* get file cluster */
static void getFileCluster(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for file cluster index */
    promptMsg("File cluster index: ");
    uint32_t fcn;
    fscanf(fin, "%u", &fcn);
    fPurge(fin);

    /* open inode */
    uint32_t ih = iOpen(in);

    /* get file cluster */
    uint32_t cn = soGetFileCluster(ih, fcn);

    /* close inode */
    iClose(ih);

    /* print result */
    if (cn != NullReference)
        resultMsg("Cluster number %u retrieved\n", cn);
    else
        resultMsg("Cluster number (nil) retrieved\n");
}

/* ******************************************** */
/* alloc file cluster */
static void allocFileCluster(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for file cluster index */
    promptMsg("File cluster index: ");
    uint32_t fcn;
    fscanf(fin, "%u", &fcn);
    fPurge(fin);

    /* open inode */
    uint32_t ih = iOpen(in);

    /* alloc file cluster */
    uint32_t cn = soAllocFileCluster(ih, fcn);

    /* save and close inode */
    iSave(ih);
    iClose(ih);

    /* print result */
    resultMsg("Cluster number %u allocated\n", cn);
}

/* ******************************************** */
/* free file clusters */
static void freeFileClusters(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for file cluster index */
    promptMsg("First file cluster index: ");
    uint32_t ffcn;
    fscanf(fin, "%u", &ffcn);
    fPurge(fin);

    /* call function */
    /* open inode */
    uint32_t ih = iOpen(in);

    /* free clusters */
    soFreeFileClusters(ih, ffcn);

    /* save and close inode */
    iSave(ih);
    iClose(ih);

    resultMsg("Operation done.\n");
}

/* ******************************************** */
/* read file cluster */
static void readFileCluster(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for file cluster index */
    promptMsg("File cluster index: ");
    uint32_t fcn;
    fscanf(fin, "%u", &fcn);
    fPurge(fin);

    /* open inode */
    uint32_t ih = iOpen(in);

    /* read cluster */
    char buf[ClusterSize];
    memset(buf, 0, ClusterSize);
    soReadFileCluster(ih, fcn, buf);

    /* close inode */
    iClose(ih);

    /* show results */
    for (int i = 0; i < BlocksPerCluster; i++)
        printBlockAsHex(buf + BlockSize * i, BlockSize * i);

    /* wait for ENTER */
    promptMsg("Press ENTER to continue");
    fscanf(fin, "%*[^\n]");
    fPurge(fin);
}

/* ******************************************** */
/* write file cluster */
static void writeFileCluster(void)
{
    /* ask for inode number */
    promptMsg("Inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for file cluster index */
    promptMsg("File cluster index: ");
    uint32_t fcn;
    fscanf(fin, "%u", &fcn);
    fPurge(fin);

    /* ask for byte pattern */
    promptMsg("Byte pattern in hexadecimal: ");
    uint8_t bpx;
    fscanf(fin, "%hhx", &bpx);
    fPurge(fin);

    /* open inode */
    uint32_t ih = iOpen(in);

    /* read cluster */
    char buf[ClusterSize];
    memset(buf, bpx, ClusterSize);
    soWriteFileCluster(ih, fcn, buf);

    /* close inode */
    iSave(ih);
    iClose(ih);
}

/* ******************************************** */
/* get direntry */
static void getDirEntry()
{
    /* ask for inode number */
    promptMsg("Parent inode number: ");
    uint32_t pin;
    fscanf(fin, "%u", &pin);
    fPurge(fin);

    /* ask for direntry name */
    promptMsg("Direntry name: ");
    char name[100];
    fscanf(fin, "%[^\n]", name);
    fPurge(fin);

    /* open parent inode */
    int pih = iOpen(pin);

    /* call function */
    uint32_t cin;
    cin = soGetDirEntry(pih, name);

    /* close inode */
    iClose(pih);

    /* print result */
    resultMsg("Child inode number = %u.\n", cin);
}

/* ******************************************** */
/* add direntry */
static void addDirEntry()
{
    /* ask for parent inode number */
    promptMsg("Parent inode number: ");
    uint32_t pin;
    fscanf(fin, "%u", &pin);
    fPurge(fin);

    /* ask for direntry name */
    promptMsg("Direntry name: ");
    char name[100];
    fscanf(fin, "%[^\n]", name);
    fPurge(fin);

    /* ask for child inode number */
    promptMsg("Child inode number: ");
    uint32_t cin;
    fscanf(fin, "%u", &cin);
    fPurge(fin);

    /* open parent and child inodes */
    int pih = iOpen(pin);

    /* call function */
    soAddDirEntry(pih, name, cin);

    /* close inodes */
    iSave(pih);
    iClose(pih);

    /* print result */
    resultMsg("Direntry added.\n");
}

/* ******************************************** */
/* rename direntry */
static void renameDirEntry()
{
    /* ask for parent inode number */
    promptMsg("Parent inode number: ");
    uint32_t pin;
    fscanf(fin, "%u", &pin);
    fPurge(fin);

    /* ask for direntry name */
    promptMsg("Direntry name: ");
    char name[100];
    fscanf(fin, "%[^\n]", name);
    fPurge(fin);

    /* ask for new direntry name */
    promptMsg("New direntry name: ");
    char newname[100];
    fscanf(fin, "%[^\n]", newname);
    fPurge(fin);

    /* open parent inode */
    int pih = iOpen(pin);

    /* call function */
    soRenameDirEntry(pih, name, newname);

    /* close inode */
    iSave(pih);
    iClose(pih);

    /* print result */
    resultMsg("Direntry renamed.\n");
}

/* ******************************************** */
/* delete direntry */
static void deleteDirEntry()
{
    /* ask for inode number */
    promptMsg("Parent inode number: ");
    uint32_t pin;
    fscanf(fin, "%u", &pin);
    fPurge(fin);

    /* ask for direntry name */
    promptMsg("Direntry name: ");
    char name[100];
    fscanf(fin, "%[^\n]", name);
    fPurge(fin);

    /* ask for clean or non clean deletion */
    promptMsg("Clean entry (y/N): ");
    char answer[100];
    fscanf(fin, "%[^\n]", answer);
fprintf(stderr, "-------------------- %s\n", answer);
    bool clean = strcasecmp(name, "y") || strcasecmp(name, "yes");
    fPurge(fin);

    /* open parent inode */
    int pih = iOpen(pin);

    /* call function */
    uint32_t cin;
    cin = soDeleteDirEntry(pih, name, clean);

    /* close inode */
    iSave(pih);
    iClose(pih);

    /* print result */
    resultMsg("Child inode number = %u.\n", cin);
}

/* ******************************************** */
/* traverse path */
void traversePath()
{
    /* ask for PATH */
    promptMsg("path: ");
    char path[500];
    fscanf(fin, "%[^\n]", path);
    fPurge(fin);

    /* call function */
    uint32_t in;
    in = soTraversePath(path);

    /* print result */
    resultMsg("inode number = %u\n", in);
}

/* ******************************************** */
/* get inode permissions */
void setInodeAccess()
{
notImplemented();
#if 0
    /* ask for inode number */
    promptMsg("inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for permissions */
    promptMsg("permissions in octal: ");
    uint32_t perm;
    fscanf(fin, "%o", &perm);
    fPurge(fin);

    /* call function */
    int ih = iOpen(in);
    iSetAccess(ih, perm);

    /* print result */
    SOInode* ip = iGetPointer(ih);
    printInode(ip, in);

    /* save and close inode */
    iSave(ih);
    iClose(ih);
#endif
}

/* ******************************************** */
/* check inode permissions */
void checkInodeAccess()
{
notImplemented();
#if 0
    /* ask for inode number */
    promptMsg("inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* ask for access mode */
    promptMsg("requested access in octal: ");
    uint16_t access;
    fscanf(fin, "%ho", &access);
    fPurge(fin);

    /* call function */
    int ih = iOpen(in);
    bool granted = iCheckAccess(ih, access);
    iClose(ih);

    /* print result */
    resultMsg("access %0s\n", granted ? "granted" : "denied");
#endif
}

/* ******************************************** */
/* dec inode refcount */
void decInodeLnkcnt()
{
notImplemented();
#if 0
    /* ask for inode number */
    promptMsg("inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* call function */
    int ih = iOpen(in);
    uint16_t rc = iDecLnkcnt(ih);
    iSave(ih);
    iClose(ih);

    /* print result */
    resultMsg("refcount = %hu\n", rc);
#endif
}

/* ******************************************** */
/* inc inode refcount */
void incInodeLnkcnt()
{
notImplemented();
#if 0
    /* ask for inode number */
    promptMsg("inode number: ");
    uint32_t in;
    fscanf(fin, "%u", &in);
    fPurge(fin);

    /* call function */
    int ih = iOpen(in);
    uint16_t rc = iIncLnkcnt(ih);
    iSave(ih);
    iClose(ih);

    /* print result */
    resultMsg("refcount = %hu\n", rc);
#endif
}

/* ******************************************** */
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
/* ******************************************** */
/* handling user choise */
typedef void (*handler) (void);
class Handler
{
public:
    std::map<std::string, handler> hdl;

    Handler()
    {
        hdl["ai"] = allocInode;
        hdl["fi"] = freeInode;
        hdl["ac"] = allocCluster;
        hdl["fc"] = freeCluster;
        hdl["r"] = replenish;
        hdl["d"] = deplete;
        hdl["afc"] = allocFileCluster;
        hdl["ffc"] = freeFileClusters;
        hdl["gfc"] = getFileCluster;
        hdl["rfc"] = readFileCluster;
        hdl["wfc"] = writeFileCluster;
        hdl["ade"] = addDirEntry;
        hdl["dde"] = deleteDirEntry;
        hdl["rde"] = renameDirEntry;
        hdl["gde"] = getDirEntry;
        hdl["tp"] = traversePath;
        hdl["sb"] = showBlock;
        hdl["s"] = showBlock;
        hdl["fd"] = formatDisk;
        hdl["f"] = formatDisk;
        hdl["cd"] = createDisk;
        hdl["c"] = createDisk;
        hdl["spd"] = setProbeDepths;
        hdl["cia"] = checkInodeAccess;
        hdl["sia"] = setInodeAccess;
        hdl["iic"] = incInodeLnkcnt;
        hdl["dic"] = decInodeLnkcnt;
    }

    void exec(std::string & key)
    {
        try
        {
            hdl.at(key)();
        }
        catch (const std::out_of_range & err)
        {
            errorMsg("Invalid choice");
        }
    }
};

class Menu
{
public:
    int quiet_mode;

    Menu() : quiet_mode(0)
    {
    }

    void printMenu(void)
    {
        if (quiet > 0)
            return;

        printf
            ("+================================================================+\n"
             "|                        testing functions                       |\n"
             "+================================================================+\n"
             "|   q - exit                     |  sb - show block              |\n"
             "|  fd - format disk              | spd - set probe depths        |\n"
             "+--------------------------------+-------------------------------+\n"
             "|  ai - alloc inode              |  fi - free inode              |\n"
             "|  ac - alloc cluster            |  fc - free cluster            |\n"
             "|   r - replenish                |   d - deplete                 |\n"
             "+--------------------------------+-------------------------------+\n"
             "| gfc - get file cluster         | afc - alloc file cluster      |\n"
             "| ffc - free file clusters       |     - NOT USED                |\n"
             "| rfc - read file cluster        | wfc - write file cluster      |\n"
             "+--------------------------------+-------------------------------+\n"
             "| gde - get dir entry            | ade - add dir entry           |\n"
             "| rde - rename dir entry         | dde - delete dir entry        |\n"
             "|  tp - traverse path            |     - NOT USED                |\n"
             "+--------------------------------+-------------------------------+\n"
             "+ cia - check inode access       | sia - set inode access        +\n"
             "+ iil - increment inode lnkcnt   | dil - decrement inode lnkcnt  +\n"
             "+================================================================+\n");
    }

    std::string & readChoice()
    {
        promptMsg("\nYour command: ");
        static std::string line;
        getline(std::cin, line);
        return line;
    }
};

/* ******************************************** */
/* The main function */
int main(int argc, char *argv[])
{
    progName = basename(argv[0]);   // must be called before dirname!
    progDir = dirname(argv[0]);

    /* ... */
    Menu menu;
    Handler handler;

    /* process command line options */
    int opt;
    while ((opt = getopt(argc, argv, "l:q:h")) != -1)
    {
        switch (opt)
        {
            case 'l':    /* log depth */
            {
                if (sscanf(optarg, "%d,%d", &lowerProbe, &upperProbe) != 2)
                {
                    errorMsg("%s: Bad argument to l option.\n", progName);
                    printUsage(progName);
                    return EXIT_FAILURE;
                }
                break;
            }
            case 'q':    /* quiet mode */
            {
                quiet = atoi(optarg);
                if (quiet < 0) quiet = 0;
                else if (quiet > 2) quiet = 2;
                break;
            }
            case 'h':    /* help mode */
            {
                printUsage(progName);
                return EXIT_SUCCESS;
            }
            default:
            {
                errorMsg("%s: Wrong option.\n", progName);
                printUsage(progName);
                return EXIT_FAILURE;
            }
        }
    }

    /* check existence of mandatory argument: storage device name */
    if ((argc - optind) != 1)
    {
        fprintf(stderr, "%s: Wrong number of mandatory arguments.\n", progName);
        printUsage(progName);
        return EXIT_FAILURE;
    }
    devname = argv[optind];

    /* set probe depths */
    soSetProbeDepths(lowerProbe, upperProbe);

    /* set log stream */
    if (flog == NULL)
        flog = stdout;    /* if the switch -L was not used, set output to stdout */
    else
        stderr = flog;    /* if the switch -L was used, set stderr to log file */

    /* open disk */
    try
    {
        soOpenDisk(devname);
    }
    catch(SOException & err)
    {
        errnoMsg(err.en, err.msg);
        return EXIT_FAILURE;
    }

    /* process the command */
    while (true)
    {
        menu.printMenu();
        std::string & opt = menu.readChoice();
        if (opt == "q" || opt == "0") break;

        try
        {
            handler.exec(opt);
        }
        catch(SOException & err)
        {
            errnoMsg(err.en, err.msg);
        }
    }

    /* close the unbuffered communication channel with the storage device */
    try
    {
        soCloseDisk();
    }
    catch(SOException & err)
    {
        errnoMsg(err.en, err.msg);
    }

    /* that's all */
    promptMsg("Bye!\n");
    return EXIT_SUCCESS;
}                /* end of main */
