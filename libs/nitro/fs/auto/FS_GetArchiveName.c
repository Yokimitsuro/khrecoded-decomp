#include "libs/nitro/fs/fs_internal.h"

const char *FS_GetArchiveName(const FSArchive *archive)
{
    return archive->name.shortName[3] != '\0'
               ? (const char *)archive->name.packed
               : archive->name.shortName;
}