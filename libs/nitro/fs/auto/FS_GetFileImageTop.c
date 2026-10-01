#include "libs/nitro/fs/fs_internal.h"

u32 FS_GetFileImageTop(const FSFile *file)
{
    const FSROMFATProperty *property =
        (const FSROMFATProperty *)file->reserved1;

    return property->file.top;
}
