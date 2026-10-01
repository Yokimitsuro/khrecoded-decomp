#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_OpenFile(FSArchive *archive, FSFile *file, u32 baseId,
                             const char *path, u32 mode)
{
    FSResult result;
    u32 fileId;

    result = FSi_ROMFAT_FindPath(archive, baseId, path, &fileId, 0);
    if (result == FS_RESULT_SUCCESS) {
        result = FSi_ROMFAT_OpenFileFast(archive, file, fileId, mode);
    }
    return result;
}
