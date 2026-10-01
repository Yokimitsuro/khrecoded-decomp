#include "libs/nitro/fs/fs_internal.h"

extern BOOL FS_OpenFileEx(FSFile *file, const char *path, u32 mode);

BOOL FS_OpenFile(FSFile *file, const char *path)
{
    return FS_OpenFileEx(file, path, 1);
}
