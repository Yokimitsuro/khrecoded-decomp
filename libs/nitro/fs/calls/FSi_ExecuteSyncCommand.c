#include "libs/nitro/fs/fs_internal.h"

extern FSResult FSi_InvokeCommand(FSFile *file, FSCommandType command);
extern FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner);
extern void FSi_ExecuteAsyncCommand(FSFile *file);

static inline void FSi_WaitConditionChange(u32 *flags, u32 on, u32 off,
                                            OSThreadQueue *queue)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    while ((!on || ((*flags & on) == 0)) &&
           (!off || ((*flags & off) != 0))) {
        OS_SleepThread(queue);
    }
    (void)OS_RestoreInterrupts(interruptState);
}

void FSi_ExecuteSyncCommand(FSFile *file)
{
    FSi_WaitConditionChange(&file->status, FS_FILE_STATUS_OPERATING,
                            FS_FILE_STATUS_BUSY, file->queue);

    if ((file->status & FS_FILE_STATUS_OPERATING) != 0) {
        FSArchive *const archive = file->archive;
        FSResult result = FSi_InvokeCommand(file, FSi_GetCurrentCommand(file));

        FSi_EndCommand(file, result);
        file = FSi_NextCommand(archive, 1);
        if (file) {
            FSi_ExecuteAsyncCommand(file);
        }
    }
}