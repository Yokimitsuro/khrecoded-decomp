#include "libs/nitro/fs/fs_internal.h"

extern void *FS_UnloadArchiveTables(FSArchive *archive);
extern BOOL FS_OpenFileDirect(FSFile *file, FSArchive *archive, u32 top,
                              u32 bottom, u32 id);
extern int FS_ReadFile(FSFile *file, void *destination, int length);
extern BOOL FS_CloseFile(FSFile *file);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);

u32 FS_LoadArchiveTables(FSArchive *archive, void *memory, u32 maxSize)
{
    FSROMFATArchiveContext *context;
    u32 totalSize;
    u8 *cache;
    FSFile file;

    if (memory != 0 && FS_IsArchiveTableLoaded(archive)) {
        (void)FS_UnloadArchiveTables(archive);
    }

    context = (FSROMFATArchiveContext *)archive->userdata;
    totalSize = (context->fatSize + context->fntSize + 63) & ~31;
    if (totalSize <= maxSize) {
        cache = (u8 *)(((u32)memory + 31) & ~31);
        FS_InitFile(&file);

        if (FS_OpenFileDirect(&file, archive, context->fat,
                              context->fat + context->fatSize, ~0UL)) {
            if (FS_ReadFile(&file, cache, (int)context->fatSize) < 0) {
                MI_CpuFill8(cache, 0, context->fatSize);
            }
            (void)FS_CloseFile(&file);
        }
        context->fat = (u32)cache;
        cache += context->fatSize;

        if (FS_OpenFileDirect(&file, archive, context->fnt,
                              context->fnt + context->fntSize, ~0UL)) {
            if (FS_ReadFile(&file, cache, (int)context->fntSize) < 0) {
                MI_CpuFill8(cache, 0, context->fntSize);
            }
            (void)FS_CloseFile(&file);
        }
        context->fnt = (u32)cache;
        context->loadedTables = memory;
        archive->flags |= FS_ARCHIVE_FLAG_TABLE_LOAD;
    }

    return totalSize;
}
