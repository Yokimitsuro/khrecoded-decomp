#include "nitro/types.h"

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
} FileLoader;

extern FileLoader gFileLoader;
extern u8 data_02053274[0x80];

extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern void openFileFromNitroRomArchive(void *file, u32 id);
extern int TileMap_GetHighBit(u32 id);
extern int strlen(const char *s);
extern char *Msg_BuildLangPath(const char *name);
extern int FS_OpenFile(void *file, char *path);
extern int FS_GetLength(void *file);
extern void FS_ReadFile(void *file, void *dst, int size);
extern int StartStreamUncompress(void *rd, void *file, void *dest, u32 *pSize, int heap, int unused1, int unused2,
                         int *pDone);
extern void FS_WaitAsync(void *file);
extern int FS_ReadFileAsync(void *file, void *dst, int size);
extern void OS_Terminate(void);
extern int MI_ReadUncompLZ8(void *ctx, void *src, int len);
extern void DC_FlushRange(void *dst, u32 size);
extern void DC_FlushAll(void);
extern void FS_CloseFile(void *file);

u32 LoadFileIntoBuffer(u32 data, void *buffer, u32 size, u32 param4)
{
    u8 file[72];
    int done;
    int compressed;
    int nameLen;
    u32 result;
    u8 *rd;

    rd = gFileLoader.reader;
    FS_InitFile(file);
    FSi_WaitForCardThread();

    if (data & 0x80000000) {
        openFileFromNitroRomArchive(file, data);
        compressed = TileMap_GetHighBit(data);
    } else {
        nameLen = strlen((char *)data);
        FS_OpenFile(file, Msg_BuildLangPath((char *)data));
        compressed = 0;
        if (((s8 *)data)[nameLen - 2] == '.') {
            s32 c = ((s8 *)data)[nameLen - 1];
            if (c >= 0 && c < 0x80) {
                c = data_02053274[c];
            }
            if (c == 'Z') {
                compressed = 1;
            }
        }
    }

    if (compressed != 0) {
        StartStreamUncompress(rd, file, buffer, &size, 0, 0, 0, &done);
        result = size;
        if (done == 0) {
            do {
                rd[0x414] ^= 1;
                rd[0x415] ^= 1;
                FS_WaitAsync(file);
                *(u32 *)(rd + rd[0x414] * 4 + 0x418) = FS_ReadFileAsync(file, rd + (rd[0x414] << 9), 0x200);
                {
                    s32 status = *(u32 *)(rd + rd[0x415] * 4 + 0x418);
                    if (status != 0 && status == -1) {
                        OS_Terminate();
                    }
                }
            } while (MI_ReadUncompLZ8(rd + 0x400, rd + (rd[0x415] << 9), *(u32 *)(rd + rd[0x415] * 4 + 0x418)) != 0);
        }
        if (result >= 0x2400) {
            DC_FlushAll();
        } else {
            DC_FlushRange(buffer, result);
        }
        FS_WaitAsync(file);
    } else {
        result = FS_GetLength(file);
        if ((s32)result > (s32)size) {
            result = 0xffffffff;
        } else {
            FS_ReadFile(file, buffer, result);
        }
    }
    FS_CloseFile(file);
    return result;
}
