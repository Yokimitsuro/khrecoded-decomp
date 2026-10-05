#include "nitro/types.h"

typedef struct StreamReader {
    u8 block[2][0x200];
    u8 uncompContext[0x14];
    u8 curBlock;
    u8 prevBlock;
    u8 pad_416[2];
    s32 blockLen[2];
} StreamReader;

typedef struct FileLoader {
    StreamReader *reader;
} FileLoader;

extern FileLoader gFileLoader;

extern s32 FS_ReadFile(void *file, void *buffer, s32 length);
extern int FS_ReadFileAsync(void *file, void *buffer, s32 length);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void MI_InitUncompContextLZ(void *context, u8 *dest, const void *header);
extern int MI_ReadUncompLZ8(void *context, void *src, int len);

u8 *StartStreamUncompress(StreamReader *reader, void *file, u8 *dest, s32 *sizeInOut, void **heap,
                                   BOOL alignFromEnd, int unused, BOOL *done)
{
    s32 size;
    StreamReader *loaderReader = gFileLoader.reader;

    reader->blockLen[0] = FS_ReadFile(file, reader, 0x200);
    size = *(u32 *)reader->block[0] >> 8;
    if (dest == NULL) {
        if (alignFromEnd) {
            dest = AllocFromHeapOrDefaultEx(size, -0x20, heap);
        } else {
            dest = AllocFromHeapOrDefaultEx(size, 0x20, heap);
        }
    } else if (size > *sizeInOut) {
        return NULL;
    }
    *sizeInOut = size;
    MI_InitUncompContextLZ(reader->uncompContext, dest, reader);
    loaderReader->blockLen[0] -= 4;
    *done = MI_ReadUncompLZ8(loaderReader->uncompContext, loaderReader->block[0] + 4, loaderReader->blockLen[0]) == 0;
    if (*done == FALSE) {
        reader->curBlock = 0;
        reader->prevBlock = 1;
        reader->blockLen[1] = 0;
        reader->blockLen[0] = 0;
        reader->blockLen[reader->curBlock] = FS_ReadFileAsync(file, reader->block[reader->curBlock], 0x200);
    }
    return dest;
}
