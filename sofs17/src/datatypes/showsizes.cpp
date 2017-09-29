#include <stdio.h>

#include "datatypes.h"

int main(void)
{
    fprintf(stdout, 
                "BlockSize: %u\n"
                "sizeof(SOSuperBlock): %lu\n"
                "sizeof(SOInode): %lu\n"
                "sizeof(SODirEntry): %lu\n"
                "ReferencesPerCluster: %lu\n"
                "ReferencesPerBitmapBlock: %u\n"
                "ReferenceBytesPerBitmapBlock: %u\n"
                "InodesPerBlock: %lu\n"
                "BlocksPerCluster: %d\n"
                "DirentriesPerCluster: %lu\n"
                "ClusterSize: %u\n",
                BlockSize, 
                sizeof(SOSuperBlock), sizeof(SOInode), sizeof(SODirEntry),
                ReferencesPerCluster, ReferencesPerBitmapBlock, ReferenceBytesPerBitmapBlock, 
                InodesPerBlock, BlocksPerCluster, 
                DirentriesPerCluster, ClusterSize);

    return 0;
}
