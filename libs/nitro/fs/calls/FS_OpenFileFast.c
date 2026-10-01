#include "libs/nitro/fs/fs_internal.h"

typedef struct FSFileID {
    FSArchive *archive;
    u32 fileId;
} FSFileID;

typedef struct FSArgumentForOpenFileFast {
    u32 id;
    u32 mode;
} FSArgumentForOpenFileFast;

#define FS_COMMAND_OPENFILEFAST 6UL

extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

BOOL FS_OpenFileFast(FSFile *file, FSFileID id)
{
    BOOL result = 0;

    if (id.archive) {
        FSArgumentForOpenFileFast argument[1];

        file->archive = id.archive;
        file->argument = argument;
        argument->id = id.fileId;
        argument->mode = 0;
        result = FSi_SendCommand(file, FS_COMMAND_OPENFILEFAST, 1);
    }
    return result;
}
