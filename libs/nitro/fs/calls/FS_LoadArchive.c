#include "libs/nitro/fs/fs_internal.h"

extern const FSArchiveInterface FSiArchiveProcInterface;
extern FSResult FSi_ReadMemCallback(FSArchive *archive, void *destination,
                                    u32 position, u32 size);
extern FSResult FSi_WriteMemCallback(FSArchive *archive, const void *source,
                                     u32 position, u32 size);
extern BOOL FS_MountArchive(FSArchive *archive, void *userdata,
                            const FSArchiveInterface *interface,
                            u32 flags);

BOOL FS_LoadArchive(FSArchive *archive, u32 base, u32 fat, u32 fatSize,
                    u32 fnt, u32 fntSize, FSArchiveReadFunction readFunction,
                    FSArchiveWriteFunction writeFunction)
{
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->reserved;

    context->base = base;
    context->fatSize = fatSize;
    context->fat = fat;
    context->fatBackup = fat;
    context->fntSize = fntSize;
    context->fnt = fnt;
    context->fntBackup = fnt;
    context->readFunction = readFunction ? readFunction : FSi_ReadMemCallback;
    context->writeFunction = writeFunction ? writeFunction : FSi_WriteMemCallback;
    context->loadedTables = 0;

    return FS_MountArchive(archive, context, &FSiArchiveProcInterface, 0);
}
