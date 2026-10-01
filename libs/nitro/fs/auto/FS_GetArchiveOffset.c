#include "libs/nitro/fs/fs_internal.h"

u32 FS_GetArchiveOffset(const FSArchive *archive, u32 position)
{
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;

    return context->base + position;
}
