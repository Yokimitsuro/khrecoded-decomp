#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_GetArchiveCaps(FSArchive *archive, u32 *capabilities)
{
    *capabilities = 0;
    (void)archive;
    return FS_RESULT_SUCCESS;
}
