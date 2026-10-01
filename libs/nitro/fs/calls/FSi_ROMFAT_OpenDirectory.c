#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_OpenDirectory(FSArchive *archive, FSFile *file,
                                  u32 baseId, const char *path, u32 mode)
{
    FSResult result;
    u32 id = 0;

    result = FSi_ROMFAT_FindPath(archive, baseId, path, &id, 1);
    if (result == FS_RESULT_SUCCESS) {
        result = FSi_ROMFAT_SeekDirectory(archive, file, id, 0);
    }
    (void)mode;
    return result;
}
