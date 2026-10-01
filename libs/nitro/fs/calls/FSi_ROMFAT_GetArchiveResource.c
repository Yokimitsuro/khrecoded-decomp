#include "libs/nitro/fs/fs_internal.h"

typedef struct CARDRomHeader {
    u8 reserved[0x80];
    u32 romSize;
} CARDRomHeader;

extern const CARDRomHeader *CARD_GetRomHeader(void);

FSResult FSi_ROMFAT_GetArchiveResource(FSArchive *archive,
                                       FSArchiveResource *resource)
{
    const CARDRomHeader *header = CARD_GetRomHeader();

    resource->bytesPerSector = 0;
    resource->sectorsPerCluster = 0;
    resource->totalClusters = 0;
    resource->availableClusters = 0;
    resource->totalSize = header->romSize;
    resource->availableSize = 0;
    resource->maxFileHandles = 0x7fffffff;
    resource->currentFileHandles = 0;
    resource->maxDirectoryHandles = 0x7fffffff;
    resource->currentDirectoryHandles = 0;
    (void)archive;
    return FS_RESULT_SUCCESS;
}
