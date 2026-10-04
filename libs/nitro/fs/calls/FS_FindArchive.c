#include "libs/nitro/fs/fs_internal.h"

extern int STD_CompareNString(const char *left, const char *right, u32 length);

FSArchive *FS_FindArchive(const char *name, u32 nameLength)
{
    OSIntrMode interruptState = OS_DisableInterrupts();
    FSArchive *archive = arc_list;

    for (; archive != 0; archive = archive->next) {
        if (FS_IsArchiveLoaded(archive)) {
            const char *archiveName = FS_GetArchiveName(archive);

            if (STD_CompareNString(archiveName, name, nameLength) == 0 &&
                archiveName[nameLength] == '\0') {
                break;
            }
        }
    }

    (void)OS_RestoreInterrupts(interruptState);
    return archive;
}