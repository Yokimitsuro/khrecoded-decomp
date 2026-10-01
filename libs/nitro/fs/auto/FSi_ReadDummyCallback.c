#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ReadDummyCallback(FSArchive *archive, void *destination,
                               u32 source, u32 length)
{
    (void)archive;
    (void)destination;
    (void)source;
    (void)length;
    return FS_RESULT_UNSUPPORTED;
}
