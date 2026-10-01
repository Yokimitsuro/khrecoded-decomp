#include "libs/nitro/fs/fs_internal.h"

extern FSResult FSi_InvokeCommand(FSFile *file, FSCommandType command);
extern FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner);

void FSi_ExecuteAsyncCommand(FSFile *file)
{
    FSArchive *const archive = file->archive;

    while (file) {
        {
            OSIntrMode interruptState = OS_DisableInterrupts();

            file->status |= FS_FILE_STATUS_OPERATING;
            if ((file->status & FS_FILE_STATUS_BLOCKING) != 0) {
                OS_WakeupThread(file->queue);
                file = 0;
            }
            (void)OS_RestoreInterrupts(interruptState);
        }
        if (!file) {
            break;
        } else if (FSi_InvokeCommand(file, FSi_GetCurrentCommand(file)) ==
                   FS_RESULT_PROC_ASYNC) {
            break;
        } else {
            file = FSi_NextCommand(archive, 1);
        }
    }
}