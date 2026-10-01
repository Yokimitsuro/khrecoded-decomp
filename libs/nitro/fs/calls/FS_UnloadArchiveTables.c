#include "libs/nitro/fs/fs_internal.h"

extern BOOL FS_SuspendArchive(FSArchive *archive);
extern BOOL FS_ResumeArchive(FSArchive *archive);

void *FS_UnloadArchiveTables(FSArchive *archive)
{
    void *memory = 0;

    if (FS_IsArchiveLoaded(archive)) {
        FSROMFATArchiveContext *context =
            (FSROMFATArchiveContext *)archive->userdata;
        BOOL wasActive = FS_SuspendArchive(archive);

        if (FS_IsArchiveTableLoaded(archive)) {
            archive->flags &= ~FS_ARCHIVE_FLAG_TABLE_LOAD;
            memory = context->loadedTables;
            context->fat = context->fatBackup;
            context->fnt = context->fntBackup;
            context->loadedTables = 0;
        }
        if (wasActive) {
            (void)FS_ResumeArchive(archive);
        }
    }

    return memory;
}
