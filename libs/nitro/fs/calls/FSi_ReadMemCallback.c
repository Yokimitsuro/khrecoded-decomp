#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);

FSResult FSi_ReadMemCallback(FSArchive *archive, void *destination,
                             u32 position, u32 size)
{
    MI_CpuCopy8((const void *)FS_GetArchiveOffset(archive, position),
                destination, size);
    return FS_RESULT_SUCCESS;
}