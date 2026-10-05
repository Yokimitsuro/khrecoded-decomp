#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    void **slots;
} ExtraTable;

typedef struct {
    u8 pad_00[0x1c8];
    ExtraTable *extra;
} Context;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);

void AllocateSlotIfNull(Context *context, int index)
{
    if (context->extra->slots[index] == 0) {
        context->extra->slots[index] = NNSi_FndAllocFromDefaultHeap(0xf2c);
        MI_CpuFill8(context->extra->slots[index], 0, 0xf2c);
    }
}
