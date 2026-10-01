#include "libs/nitro/fs/fs_internal.h"

extern const struct FSArchiveInterface FSiArchiveProcInterface;
extern FSResult FSi_ROMFAT_GetFilePosition(FSArchive *archive, FSFile *file, u32 *value);

BOOL FSi_GetFilePositionIfProc(FSFile *file, u32 *value)
{
    return file->archive->interface == &FSiArchiveProcInterface &&
           FSi_ROMFAT_GetFilePosition(file->archive, file, value) == FS_RESULT_SUCCESS;
}
