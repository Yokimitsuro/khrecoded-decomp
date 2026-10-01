#include "libs/nitro/fs/fs_internal.h"

BOOL FS_SuspendArchive(FSArchive *archive)
{
    BOOL suspended = 0;
    OSIntrMode interruptState = OS_DisableInterrupts();

    suspended = !FS_IsArchiveSuspended(archive);
    if (suspended) {
        if ((archive->flags & FS_ARCHIVE_FLAG_RUNNING) == 0) {
            archive->flags |= FS_ARCHIVE_FLAG_SUSPEND;
        } else {
            archive->flags |= FS_ARCHIVE_FLAG_SUSPENDING;
            FSi_WaitConditionOff(&archive->flags, FS_ARCHIVE_FLAG_SUSPENDING,
                                 &archive->queue);
        }
    }
    (void)OS_RestoreInterrupts(interruptState);
    return suspended;
}
