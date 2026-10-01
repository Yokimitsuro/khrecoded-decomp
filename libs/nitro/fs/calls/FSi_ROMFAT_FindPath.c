#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_FindPath(FSArchive *archive, u32 baseDirectoryId,
                             const char *path, u32 *targetId,
                             BOOL targetIsDirectory)
{
    FSResult result;
    union {
        FSFileID file;
        FSDirPos directory;
    } id;
    FSFile temporary[1];

    FS_InitFile(temporary);
    temporary->archive = archive;
    ((FSFindPathInfo *)temporary->reserved2)->position.archive = archive;
    ((FSFindPathInfo *)temporary->reserved2)->position.ownId =
        (u16)(baseDirectoryId >> 0);
    ((FSFindPathInfo *)temporary->reserved2)->position.index = 0;
    ((FSFindPathInfo *)temporary->reserved2)->position.position = 0;
    ((FSFindPathInfo *)temporary->reserved2)->path = path;
    ((FSFindPathInfo *)temporary->reserved2)->findDirectory =
        targetIsDirectory;
    if (targetIsDirectory) {
        ((FSFindPathInfo *)temporary->reserved2)->result.directory =
            &id.directory;
    } else {
        ((FSFindPathInfo *)temporary->reserved2)->result.file = &id.file;
    }
    result = FSi_TranslateCommand(temporary, FS_COMMAND_FINDPATH, 1);
    if (result == FS_RESULT_SUCCESS) {
        if (targetIsDirectory) {
            *targetId = id.directory.ownId;
        } else {
            *targetId = id.file.fileId;
        }
    }
    return result;
}