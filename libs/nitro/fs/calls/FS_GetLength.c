#include "libs/nitro/fs/fs_internal.h"

u32 FS_GetLength(FSFile *file)
{
    return FS_GetFileLength(file);
}
