#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);

FSResult FSi_WriteMemCallback(FSArchive *archive, const void *source,
                              u32 position, u32 size)
{
    MI_CpuCopy8(source, (void *)FS_GetArchiveOffset(archive, position), size);
    return FS_RESULT_SUCCESS;
}