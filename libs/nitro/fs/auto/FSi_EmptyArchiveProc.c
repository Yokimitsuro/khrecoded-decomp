#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_EmptyArchiveProc(FSFile *file, FSCommandType command)
{
    (void)file;
    switch (command) {
    case FS_COMMAND_WRITEFILE:
        return FS_RESULT_UNSUPPORTED;
    default:
        return FS_RESULT_PROC_UNKNOWN;
    }
}
