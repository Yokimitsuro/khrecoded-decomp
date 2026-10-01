#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_GetFilePosition(FSArchive *archive, FSFile *file,
                                    u32 *position)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->userdata;

    *position = property->position - property->top;
    (void)archive;
    return FS_RESULT_SUCCESS;
}
