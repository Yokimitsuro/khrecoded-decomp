#include "libs/nitro/fs/fs_internal.h"

extern const struct FSArchiveInterface FSiArchiveProcInterface;
extern FSResult FSi_ROMFAT_GetFileLength(FSArchive *archive, FSFile *file, u32 *value);

BOOL FSi_GetFileLengthIfProc(FSFile *file, u32 *value)
{
    return file->archive->interface == &FSiArchiveProcInterface &&
           FSi_ROMFAT_GetFileLength(file->archive, file, value) == FS_RESULT_SUCCESS;
}
