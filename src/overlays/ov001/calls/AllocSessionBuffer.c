#include "nitro/types.h"

typedef struct {
    void *data;
    u32 size;
} SessionBuffer;

extern u32 data_ov001_020a0480;
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);

void *AllocSessionBuffer(int index, u32 size)
{
    SessionBuffer *buffers = (SessionBuffer *)(data_ov001_020a0480 + 0x283c);
    SessionBuffer *entry = &buffers[index];

    buffers[index].data = NNS_FndAllocFromDefaultExpHeapEx(size, -4);
    entry->size = size;
    return buffers[index].data;
}
