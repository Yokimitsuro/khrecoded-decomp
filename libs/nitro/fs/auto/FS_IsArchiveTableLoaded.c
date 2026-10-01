#include "libs/nitro/fs/fs_internal.h"

BOOL FS_IsArchiveTableLoaded(volatile const FSArchive *archive)
{
    return (archive->flags & FS_ARCHIVE_FLAG_TABLE_LOAD) != 0;
}
