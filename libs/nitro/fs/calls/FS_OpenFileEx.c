#include "libs/nitro/fs/fs_internal.h"

typedef struct FSArgumentForOpenFile {
    u32 baseId;
    const char *relativePath;
    u32 mode;
} FSArgumentForOpenFile;

#define FS_ARCHIVE_FULLPATH_MAX 277
#define FS_COMMAND_OPENFILE 13UL

extern FSArchive *FS_NormalizePath(const char *path, u32 *baseId,
                                   char *relativePath);
extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

BOOL FS_OpenFileEx(FSFile *file, const char *path, u32 mode)
{
    BOOL result = 0;
    char relativePath[FS_ARCHIVE_FULLPATH_MAX + 1];
    u32 baseId = 0;
    FSArchive *archive = FS_NormalizePath(path, &baseId, relativePath);

    if (archive) {
        FSArgumentForOpenFile argument[1];

        FS_InitFile(file);
        file->archive = archive;
        file->argument = argument;
        argument->baseId = baseId;
        argument->relativePath = relativePath;
        argument->mode = mode;
        if (FSi_SendCommand(file, FS_COMMAND_OPENFILE, 1)) {
            result = 1;
        } else {
            file->archive = 0;
        }
    }
    return result;
}
