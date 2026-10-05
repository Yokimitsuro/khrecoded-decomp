#include "nitro/types.h"

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    void **heap;
} FileLoader;

extern FileLoader gFileLoader;
extern u8 data_02053274[0x80];

extern void *AllocLoaderRequest(void);
extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern void openFileFromNitroRomArchive(void *file, u32 id);
extern int TileMap_GetHighBit(u32 id);
extern int strlen(const char *s);
extern char *Msg_BuildLangPath(const char *name);
extern int FS_OpenFile(void *file, char *path);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void PrepareCompressedLoad(void *handle, void *file, int a, int b, void **heap, int alignMode, int param3);
extern void FS_CloseFile(void *file);
extern void OS_SendMessage(void *queue, void *msg, int flags);
extern u8 data_02060584;

typedef struct LoadHandle {
    u8 pad_00[4];
    s32 mode;
    u32 field8;
    u32 fileStart;
    u32 fileEnd;
    u8 pad_14[0x28 - 0x14];
    void *buffer;
    s32 size;
} LoadHandle;

u32 RequestFileLoad(u32 data, int alignMode, int param3, u32 param4)
{
    u8 file[72];
    LoadHandle *handle;
    int nameLen;
    int compressed;

    handle = AllocLoaderRequest();
    if (handle == 0) {
        return 0;
    }

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

    handle->field8 = *(u32 *)(file + 8);
    handle->fileStart = *(u32 *)(file + 0x24);
    handle->fileEnd = *(u32 *)(file + 0x28);

    if (compressed != 0) {
        PrepareCompressedLoad(handle, file, 0, 0, gFileLoader.heap, alignMode, param3);
        handle->mode = 1;
    } else {
        handle->size = handle->fileEnd - handle->fileStart;
        if (alignMode != 0) {
            handle->buffer = AllocFromHeapOrDefaultEx(handle->size, 0xffffffe0, gFileLoader.heap);
        } else {
            handle->buffer = AllocFromHeapOrDefaultEx(handle->size, 0x20, gFileLoader.heap);
        }
        handle->mode = 0;
    }
    gFileLoader.heap = 0;
    FS_CloseFile(file);
    OS_SendMessage(&data_02060584, handle, 1);
    return (u32)handle->buffer;
}
