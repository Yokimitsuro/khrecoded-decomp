#include "nitro/types.h"

typedef struct StridedBuffer {
    u8 pad_00[0x44];
    u16 stride;
    u8 pad_46[2];
    u8 *data;
} StridedBuffer;

void *GetStridedBufferEntry(const StridedBuffer *buffer, u32 index)
{
    return buffer->data + buffer->stride * index;
}
