#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_WriteDummyCallback(FSArchive *archive, const void *source,
                                u32 destination, u32 length)
{
    (void)archive;
    (void)source;
    (void)destination;
    (void)length;
    return FS_RESULT_UNSUPPORTED;
}
