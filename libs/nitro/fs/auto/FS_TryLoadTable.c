#include "libs/nitro/fs/fs_internal.h"

extern u32 FS_LoadArchiveTables(FSArchive *archive, void *memory, u32 size);

u32 FS_TryLoadTable(void *memory, u32 size)
{
    return FS_LoadArchiveTables(&fsi_rom_archive_state.archive, memory, size);
}