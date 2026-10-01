#include "libs/nitro/fs/fs_internal.h"

BOOL FS_ResumeArchive(FSArchive *archive)
{
    BOOL wasActive;
    OSIntrMode interruptState = OS_DisableInterrupts();

    wasActive = !FS_IsArchiveSuspended(archive);
    if (!wasActive) {
        archive->flags &= ~FS_ARCHIVE_FLAG_SUSPEND;
    }
    (void)OS_RestoreInterrupts(interruptState);

    {
        FSFile *file = FSi_NextCommand(archive, 1);
        if (file) {
            FSi_ExecuteAsyncCommand(file);
        }
    }
    return wasActive;
}
