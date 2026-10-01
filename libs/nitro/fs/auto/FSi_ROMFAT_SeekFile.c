#include "libs/nitro/fs/fs_internal.h"

#define FS_SEEK_SET 0
#define FS_SEEK_CUR 1
#define FS_SEEK_END 2

FSResult FSi_ROMFAT_SeekFile(FSArchive *archive, FSFile *file, int *offset,
                             int origin)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->userdata;
    int position = *offset;

    switch (origin) {
    case FS_SEEK_SET:
        position += property->top;
        break;
    case FS_SEEK_CUR:
    default:
        position += property->position;
        break;
    case FS_SEEK_END:
        position += property->bottom;
        break;
    }

    if (position < (int)property->top || position > (int)property->bottom) {
        return FS_RESULT_INVALID_PARAMETER;
    }

    property->position = (u32)position;
    *offset = position;
    (void)archive;
    return FS_RESULT_SUCCESS;
}
