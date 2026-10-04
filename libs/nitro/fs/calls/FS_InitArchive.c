#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuFill8(void *destination, u8 value, u32 length);

void FS_InitArchive(FSArchive *archive)
{
    MI_CpuFill8(archive, 0, sizeof(*archive));
    archive->queue.tail = 0;
    archive->queue.head = 0;
}