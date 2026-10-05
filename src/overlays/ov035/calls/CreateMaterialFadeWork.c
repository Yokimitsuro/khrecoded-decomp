#include "nitro/types.h"

typedef struct FadeWork {
    u8 unknown_000[0x104];
    s16 paramA;
    s16 paramB;
    u8 unknown_108;
    s8 current;
    u8 count;
    u8 unknown_10b;
    u8 *entries;
} FadeWork;

extern FadeWork *data_ov035_020bc504;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(int value, void *dest, u32 size);
extern void MI_CpuFill8(void *dest, int value, u32 size);

void CreateMaterialFadeWork(s16 paramA, s16 paramB, int count) {
    FadeWork *work;
    u32 size;

    data_ov035_020bc504 = NNSi_FndAllocFromDefaultHeap(sizeof(FadeWork));
    MIi_CpuClearFast(0, data_ov035_020bc504, sizeof(FadeWork));
    work = data_ov035_020bc504;
    work->current = -1;
    work->count = count;
    size = count * 4;
    work->entries = NNSi_FndAllocFromDefaultHeap(size);
    MI_CpuFill8(work->entries, 0xff, size);
    work->paramA = paramA;
    work->paramB = paramB;
}
