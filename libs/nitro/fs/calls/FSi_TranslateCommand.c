#include "libs/nitro/fs/fs_internal.h"

extern FSResult (*const fsi_default_command[])(FSFile *file);

FSResult FSi_TranslateCommand(FSFile *file, FSCommandType command,
                              BOOL blocking)
{
    FSResult result = FS_RESULT_PROC_DEFAULT;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)file->archive->userdata;
    const u32 mask = 1UL << command;

    if ((context->procedureFlags & mask) != 0) {
        switch (result = context->procedure(file, command)) {
        case FS_RESULT_SUCCESS:
        case FS_RESULT_FAILURE:
        case FS_RESULT_UNSUPPORTED:
        case FS_RESULT_PROC_ASYNC:
            break;
        case FS_RESULT_PROC_UNKNOWN:
            result = FS_RESULT_PROC_DEFAULT;
            context->procedureFlags &= ~mask;
            break;
        }
    }

    if (result == FS_RESULT_PROC_DEFAULT) {
        if (command >= 13) {
            result = FS_RESULT_UNSUPPORTED;
        } else {
            result = fsi_default_command[command](file);
        }
    }

    if (blocking) {
        result = FSi_WaitForArchiveCompletion(file, result);
    }
    return result;
}