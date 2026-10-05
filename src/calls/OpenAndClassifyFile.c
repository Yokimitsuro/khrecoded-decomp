#include "nitro/types.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 mode;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1c;
} FileState;

typedef struct FSFile FSFile;

extern void FS_InitFile(FileState *state);
extern void FSi_WaitForCardThread();
extern BOOL openFileFromNitroRomArchive(FSFile *file, u32 fileId);
extern u32 TileMap_GetHighBit(u32 packedCoordinate);
extern int strlen(const u8 *str);
extern char *Msg_BuildLangPath(const char *src);
extern int FS_OpenFile(FSFile *file, char *langPath);
extern u32 FS_GetLength(FSFile *file);
extern void FS_ReadFile(FSFile *file, int value, u32 size);
extern const u8 data_02053274[];
extern int *gFileLoader[];

u32 OpenAndClassifyFile(u32 fileId)
{
    u8 buffer[0x48];
    u32 state = (u32)buffer;
    int compressed;

    FS_InitFile((FileState *)state);
    FSi_WaitForCardThread();

    if (fileId & 0x80000000) {
        u32 opened = openFileFromNitroRomArchive((FSFile *)state, fileId);
        compressed = TileMap_GetHighBit(fileId);
        state = opened;
    } else {
        int length = strlen((const u8 *)fileId);
        char *langPath = Msg_BuildLangPath((const char *)fileId);
        u32 opened = FS_OpenFile((FSFile *)state, langPath);

        compressed = 0;
        if (((const s8 *)fileId)[length - 2] == '.') {
            int c = ((const s8 *)fileId)[length - 1];

            if (c >= 0 && c < 0x80) {
                c = data_02053274[c];
            }
            if (c == 0x5a) {
                compressed = 1;
            }
        }
        state = opened;
    }

    if (state == 0) {
        return 0;
    }
    if (compressed == 0) {
        goto Simple;
    }
    {
        int *ptr = gFileLoader[0];
        FS_ReadFile((FSFile *)buffer, (int)ptr, 0x200);
        return (u32)*ptr >> 8;
    }

Simple:
    return FS_GetLength((FSFile *)buffer);
}
