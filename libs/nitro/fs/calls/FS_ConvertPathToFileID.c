#include "libs/nitro/fs/fs_internal.h"

typedef struct FSArgumentForFindPath {
    u32 baseId;
    const char *relativePath;
    u32 targetId;
    BOOL targetIsDirectory;
} FSArgumentForFindPath;

#define FS_ARCHIVE_FULLPATH_MAX 277
#define FS_COMMAND_FINDPATH 4UL

extern FSArchive *FS_NormalizePath(const char *path, u32 *baseId,
                                   char *relativePath);
extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

BOOL FS_ConvertPathToFileID(FSFileID *fileId, const char *path)
{
    BOOL result = 0;
    char relativePath[FS_ARCHIVE_FULLPATH_MAX + 1];
    u32 baseId = 0;
    FSArchive *archive = FS_NormalizePath(path, &baseId, relativePath);

    if (archive) {
        FSFile file[1];
        FSArgumentForFindPath argument[1];

        FS_InitFile(file);
        file->archive = archive;
        file->argument = argument;
        argument->baseId = baseId;
        argument->relativePath = relativePath;
        argument->targetIsDirectory = 0;
        if (FSi_SendCommand(file, FS_COMMAND_FINDPATH, 1)) {
            fileId->archive = archive;
            fileId->fileId = argument->targetId;
            result = 1;
        }
    }
    return result;
}
