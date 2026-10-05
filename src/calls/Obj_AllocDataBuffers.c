#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *bufferA;
    void *bufferB;
    void *bufferC;
    s16 count;
    u8 pad_26[6];
    u8 flag2C;
} DataBuffers;

extern void *MIi_CpuClear32(u32 value, void *dest, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);

void Obj_AllocDataBuffers(DataBuffers *obj, s32 count, s32 wantA, s32 wantB, s32 wantC)
{
    void *buf;

    if (wantA == 0) {
        buf = 0;
    } else {
        buf = NNSi_FndAllocFromDefaultHeap(count << 2);
    }
    obj->bufferA = buf;

    if (wantB == 0) {
        buf = 0;
    } else {
        buf = NNSi_FndAllocFromDefaultHeap(count << 2);
    }
    obj->bufferB = buf;

    if (wantC == 0) {
        buf = 0;
    } else {
        buf = NNSi_FndAllocFromDefaultHeap(count << 2);
    }
    obj->bufferC = buf;

    MIi_CpuClear32(0, obj, 0x18);
    obj->count = (s16)count;
    obj->flag2C = 0;
}
