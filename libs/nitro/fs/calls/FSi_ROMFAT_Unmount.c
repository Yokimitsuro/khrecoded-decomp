#include "libs/nitro/fs/fs_internal.h"

void FSi_ROMFAT_Unmount(FSArchive *archive)
{
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;

    if (FS_IsArchiveTableLoaded(archive)) {
    }
    context->base = 0;
    context->fat = 0;
    context->fatSize = 0;
    context->fnt = 0;
    context->fntSize = 0;
    context->fatBackup = 0;
    context->fntBackup = 0;
}
