#include "nitro/types.h"

typedef struct LoaderRequest {
    u8 pad_00[0x14];
    u8 uncompressContext[0x28 - 0x14];
    u8 *dest;
    s32 size;
} LoaderRequest;

extern s32 FS_ReadFile(void *file, void *buffer, s32 length);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void MI_InitUncompContextLZ(void *context, u8 *dest, const void *header);

u8 *PrepareCompressedLoad(LoaderRequest *request, void *file, u8 *dest, s32 maxSize, void **heap,
                                   BOOL alignFromEnd)
{
    u32 header;
    s32 size;

    FS_ReadFile(file, &header, 4);
    size = header >> 8;
    if (dest == NULL) {
        if (alignFromEnd) {
            dest = AllocFromHeapOrDefaultEx(size, -0x20, heap);
        } else {
            dest = AllocFromHeapOrDefaultEx(size, 0x20, heap);
        }
    } else if (size > maxSize) {
        return NULL;
    }
    request->dest = dest;
    request->size = size;
    MI_InitUncompContextLZ(request->uncompressContext, dest, &header);
    return dest;
}
