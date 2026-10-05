#include "nitro/types.h"

typedef struct StreamBuffer {
    u8 pad_00[8];
    u32 size;
    void *data;
} StreamBuffer;

typedef struct StreamSlot {
    StreamBuffer *buffer;
    u8 pad_04[8];
} StreamSlot;

typedef struct MovieScene {
    u8 pad_000[0x8e0];
    StreamSlot slots[1];
} MovieScene;

typedef struct StreamRequest {
    u8 pad_00[6];
    u16 slot;
} StreamRequest;

extern void GX_LoadBGPltt(void *dest, u32 srcOffset, u32 size, u32 unused);

BOOL MovieScene_LoadSlotBuffer(MovieScene *scene, void *unused, StreamRequest *request, u32 arg)
{
    StreamBuffer *buffer = scene->slots[request->slot].buffer;

    if (request->slot != 0x1a) {
        GX_LoadBGPltt(buffer->data, 0, buffer->size - 0x20, arg);
    } else {
        GX_LoadBGPltt(buffer->data, 0, buffer->size, arg);
    }
    return TRUE;
}
