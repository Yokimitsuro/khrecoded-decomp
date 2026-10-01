#include "libs/nitro/fs/fs_internal.h"

extern BOOL FS_OpenFileDirect(FSFile *file, FSArchive *archive, u32 top,
                              u32 bottom, u32 id);

BOOL FS_CreateFileFromRom(FSFile *file, u32 offset, u32 size)
{
    return FS_OpenFileDirect(file, &fsi_rom_archive_state.archive, offset, offset + size,
                             0xffff);
}