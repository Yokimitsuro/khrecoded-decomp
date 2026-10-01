#include "libs/nitro/fs/fs_internal.h"

extern int CARDi_ReadRom(int dma, int src, int dst, int len, int callback, int callbackArg, int isAsync);
extern int FSi_OnRomReadDone(void);

typedef struct {
    char overlayArchiveName[4];
    char pathRootSuffix[4];
    char romArchiveName[4];
    char romRootPath[8];
} FSPathStrings;

FSPathStrings fsi_path_strings = {
    "rom",
    ":/",
    "rom",
    "rom:"
};

FSRomArchiveState fsi_rom_archive_state;

int FSi_ReadRomCallback(int archive, int dst, int src, int len)
{
    CARDi_ReadRom(fsi_rom_archive_state.defaultDmaNo, src, dst, len,
                  (int)FSi_OnRomReadDone, archive, 1);
    return 0x100;
}