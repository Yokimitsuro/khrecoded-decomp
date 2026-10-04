#include "libs/nitro/fs/fs_internal.h"

typedef struct FSGlobalState {
    FSArchive *archiveList;
    FSDirPos currentDirectory;
} FSGlobalState;

typedef struct FSArgumentForFindPath {
    u32 baseDirectoryId;
    const char *relativePath;
    u32 targetId;
    BOOL targetIsDirectory;
} FSArgumentForFindPath;

#define fsi_archive_state (*(FSGlobalState *)&arc_list)
extern char current_dir_path[260];
extern int STD_CopyLString(char *destination, const char *source, int length);

BOOL FS_SetCurrentDirectory(const char *path)
{
    BOOL result = 0;
    FSArchive *archive = 0;
    u32 baseDirectoryId = 0;
    char relativePath[260];

    archive = FS_NormalizePath(path, &baseDirectoryId, relativePath);
    if (archive != 0) {
        fsi_archive_state.currentDirectory.archive = archive;
        fsi_archive_state.currentDirectory.ownId = 0;
        fsi_archive_state.currentDirectory.index = 0;
        fsi_archive_state.currentDirectory.position = 0;
        (void)STD_CopyLString(current_dir_path, relativePath,
                              sizeof(current_dir_path));

        if (archive->interface->findPath != 0) {
            FSFile directory;
            FSArgumentForFindPath argument;

            FS_InitFile(&directory);
            directory.archive = archive;
            directory.argument = &argument;
            argument.baseDirectoryId = baseDirectoryId;
            argument.relativePath = relativePath;
            argument.targetIsDirectory = 1;
            if (FSi_SendCommand(&directory, FS_COMMAND_FINDPATH, 1)) {
                fsi_archive_state.currentDirectory.ownId =
                    (u16)argument.targetId;
                (void)STD_CopyLString(current_dir_path, relativePath,
                                      sizeof(current_dir_path));
            }
        }
        result = 1;
    }
    return result;
}