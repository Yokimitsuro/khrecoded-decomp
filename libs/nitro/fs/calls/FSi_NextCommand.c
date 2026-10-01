#include "libs/nitro/fs/fs_internal.h"

#define FS_ARCHIVE_FLAG_SUSPEND 0x00000008UL
#define FS_ARCHIVE_FLAG_RUNNING 0x00000010UL
#define FS_ARCHIVE_FLAG_CANCELING 0x00000020UL
#define FS_ARCHIVE_FLAG_SUSPENDING 0x00000040UL

extern FSResult FSi_InvokeCommand(FSFile *file, FSCommandType command);
extern void FS_InitFile(FSFile *file);

static inline BOOL FS_IsCanceling(volatile const FSFile *file)
{
    return (file->status & FS_FILE_STATUS_CANCEL) != 0;
}

FSFile *FSi_NextCommand(FSArchive *archive, BOOL owner)
{
    FSFile *next = 0;

    {
        OSIntrMode interruptState = OS_DisableInterrupts();
        if ((archive->flags & FS_ARCHIVE_FLAG_CANCELING) != 0) {
            FSFile *file = archive->list;
            archive->flags &= ~FS_ARCHIVE_FLAG_CANCELING;
            while (file != 0) {
                FSFile *following = file->next;

                if (FS_IsCanceling(file) &&
                    ((file->status & FS_FILE_STATUS_OPERATING) == 0)) {
                    FSi_EndCommand(file, FS_RESULT_CANCELED);
                    if (!following) {
                        following = archive->list;
                    }
                }
                file = following;
            }
        }
        (void)OS_RestoreInterrupts(interruptState);
    }

    {
        OSIntrMode interruptState = OS_DisableInterrupts();
        if (((archive->flags & FS_ARCHIVE_FLAG_SUSPENDING) == 0) &&
            ((archive->flags & FS_ARCHIVE_FLAG_SUSPEND) == 0) &&
            archive->list) {
            const BOOL started =
                owner && ((archive->flags & FS_ARCHIVE_FLAG_RUNNING) == 0);
            if (started) {
                archive->flags |= FS_ARCHIVE_FLAG_RUNNING;
            }
            (void)OS_RestoreInterrupts(interruptState);
            if (started) {
                (void)FSi_InvokeCommand(archive->list, FS_COMMAND_ACTIVATE);
            }
            interruptState = OS_DisableInterrupts();

            if (owner || started) {
                next = archive->list;
                next->status |= FS_FILE_STATUS_OPERATING;
            }

            if (owner && ((next->status & FS_FILE_STATUS_BLOCKING) != 0)) {
                OS_WakeupThread(next->queue);
                next = 0;
            }
            (void)OS_RestoreInterrupts(interruptState);
        } else {
            if (owner) {
                if ((archive->flags & FS_ARCHIVE_FLAG_RUNNING) != 0) {
                    FSFile temporary;

                    FS_InitFile(&temporary);
                    temporary.archive = archive;
                    archive->flags &= ~FS_ARCHIVE_FLAG_RUNNING;
                    (void)FSi_InvokeCommand(&temporary, FS_COMMAND_IDLE);
                }

                if ((archive->flags & FS_ARCHIVE_FLAG_SUSPENDING) != 0) {
                    archive->flags &= ~FS_ARCHIVE_FLAG_SUSPENDING;
                    archive->flags |= FS_ARCHIVE_FLAG_SUSPEND;
                    OS_WakeupThread(&archive->queue);
                }
            }
            (void)OS_RestoreInterrupts(interruptState);
        }
    }
    return next;
}