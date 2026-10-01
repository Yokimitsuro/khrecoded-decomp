#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_GetFileLength(FSArchive *archive, FSFile *file,
                                  u32 *length)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->userdata;

    *length = property->bottom - property->top;
    (void)archive;
    return FS_RESULT_SUCCESS;
}
