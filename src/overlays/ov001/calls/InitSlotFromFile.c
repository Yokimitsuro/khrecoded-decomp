#include "nitro/types.h"

typedef struct SpriteSlot {
    u8 pad_00[0x2c];
    void *resource;
} SpriteSlot;

extern void MI_CpuFill8(void *dst, int value, int size);
extern void *Archive_LoadFile(u32 fileId, u32 flags);
extern void RebindSlotTexture(SpriteSlot *slot, int freeResource, int stopAnimation, u32 cellIndex);

BOOL InitSlotFromFile(SpriteSlot *slot, u32 fileId)
{
    MI_CpuFill8(slot, 0, sizeof(SpriteSlot));
    slot->resource = Archive_LoadFile(fileId, 0x11);
    RebindSlotTexture(slot, 1, 1, 0);
    return TRUE;
}
