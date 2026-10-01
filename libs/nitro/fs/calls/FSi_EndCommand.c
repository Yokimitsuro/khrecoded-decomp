#include "libs/nitro/fs/fs_internal.h"

void FSi_EndCommand(FSFile *file, FSResult result)
{
    OSIntrMode interruptState = OS_DisableInterrupts();
    FSArchive *const archive = file->archive;

    if (archive) {
        FSFile **link = &archive->list;

        for (; *link; link = &(*link)->next) {
            if (*link == file) {
                *link = file->next;
                break;
            }
        }
        file->next = 0;
    }

    {
        FSCommandType command = FSi_GetCurrentCommand(file);

        if (!FSi_IsEventCommand(command) && archive) {
            archive->command = command;
            archive->result = result;
        }
        file->error = result;
        file->status &= ~(FS_FILE_STATUS_CANCEL | FS_FILE_STATUS_BUSY |
                          FS_FILE_STATUS_BLOCKING | FS_FILE_STATUS_OPERATING |
                          FS_FILE_STATUS_ASYNC_DONE |
                          FS_FILE_STATUS_UNICODE_MODE);
    }

    OS_WakeupThread(file->queue);
    (void)OS_RestoreInterrupts(interruptState);
}