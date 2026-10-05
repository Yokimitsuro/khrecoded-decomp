#include "nitro/types.h"

typedef struct LoadStream {
    u8 sector[2][0x200];
    u8 decompressState[0x14];
    u8 readIndex;
    u8 useIndex;
    u8 pad_416[2];
    s32 readLen[2];
} LoadStream;

typedef struct FileLoader {
    LoadStream *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    void **heap;
} FileLoader;

extern FileLoader gFileLoader;
extern u8 data_02053274[0x80];

extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern BOOL openFileFromNitroRomArchive(void *file, u32 id);
extern int TileMap_GetHighBit(u32 id);
extern int strlen(const char *s);
extern char *Msg_BuildLangPath(const char *name);
extern BOOL FS_OpenFile(void *file, char *path);
extern void *StartStreamUncompress(LoadStream *stream, void *file, void *dest, u32 *pSize, void **heap, int alignMode,
                           int kind, int *pDone);
extern void FS_WaitAsync(void *file);
extern int FS_ReadFileAsync(void *file, void *dst, int size);
extern void OS_Terminate(void);
extern int MI_ReadUncompLZ8(void *context, void *src, int len);
extern void DC_FlushAll(void);
extern void DC_FlushRange(void *buffer, u32 size);
extern u32 FS_GetLength(void *file);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void FS_ReadFile(void *file, void *dst, u32 size);
extern void FS_CloseFile(void *file);

void *FileLoader_LoadAlloc(u32 data, int alignMode, int kind, u32 unused)
{
    u8 file[0x48];
    u32 size;
    int done;
    int opened;
    int compressed;
    void *buffer;
    LoadStream *stream = gFileLoader.reader;

    FS_InitFile(file);
    FSi_WaitForCardThread();

    if (data & 0x80000000) {
        opened = openFileFromNitroRomArchive(file, data);
        compressed = TileMap_GetHighBit(data);
    } else {
        int nameLen = strlen((char *)data);
        opened = FS_OpenFile(file, Msg_BuildLangPath((char *)data));
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

    if (opened == 0) {
        return 0;
    }

    if (compressed != 0) {
        buffer = StartStreamUncompress(stream, file, 0, &size, gFileLoader.heap, alignMode, kind, &done);
        if (done == 0) {
            do {
                stream->readIndex ^= 1;
                stream->useIndex ^= 1;
                FS_WaitAsync(file);
                stream->readLen[stream->readIndex] = FS_ReadFileAsync(file, stream->sector[stream->readIndex], 0x200);
                if (stream->readLen[stream->useIndex] != 0 && stream->readLen[stream->useIndex] == -1) {
                    OS_Terminate();
                }
            } while (MI_ReadUncompLZ8(stream->decompressState, stream->sector[stream->useIndex],
                                   stream->readLen[stream->useIndex]) != 0);
        }
        if (size >= 0x2400) {
            DC_FlushAll();
        } else {
            DC_FlushRange(buffer, size);
        }
        FS_WaitAsync(file);
    } else {
        size = FS_GetLength(file);
        if (alignMode != 0) {
            buffer = AllocFromHeapOrDefaultEx(size, -0x20, gFileLoader.heap);
        } else {
            buffer = AllocFromHeapOrDefaultEx(size, 0x20, gFileLoader.heap);
        }
        if (buffer != 0) {
            FS_ReadFile(file, buffer, size);
        }
    }
    gFileLoader.heap = 0;
    FS_CloseFile(file);
    return buffer;
}
