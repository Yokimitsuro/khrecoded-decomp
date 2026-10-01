#include "libs/nitro/fs/fs_internal.h"

BOOL FS_MountArchive(FSArchive *archive, void *userdata,
                     const FSArchiveInterface *interface, u32 reserved)
{
    FSFile file;

    (void)reserved;
    archive->userdata = userdata;
    archive->interface = interface;
    FS_InitFile(&file);
    file.archive = archive;
    (void)FSi_InvokeCommand(&file, FS_COMMAND_MOUNT);
    archive->flags |= FS_ARCHIVE_FLAG_LOADED;
    return 1;
}
