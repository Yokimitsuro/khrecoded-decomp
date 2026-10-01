#include "libs/nitro/fs/fs_internal.h"

#define FS_COMMAND_CLOSEFILE 8UL

extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

BOOL FS_CloseFile(FSFile *file)
{
    return FSi_SendCommand(file, FS_COMMAND_CLOSEFILE, 1);
}
