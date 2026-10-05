#include "nitro/types.h"

extern u32 data_ov035_020bc500;
extern void MIi_CpuClearFast(int value, void *dest, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseMovieResources(void) {
    u32 base;
    void *inner;

    base = data_ov035_020bc500;
    if (*(void **)(base + 0x50) != 0) {
        inner = *(void **)(*(u32 *)(base + 0x50) + 0x14);
        if (inner != 0) {
            NNSi_FndFreeFromDefaultHeap(inner);
        }
        NNSi_FndFreeFromDefaultHeap(*(void **)(base + 0x50));
        *(u32 *)(base + 0x50) = 0;
    }
    if (*(void **)(base + 100) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(base + 100));
    }
    if (*(void **)(base + 0x68) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(base + 0x68));
    }
    MIi_CpuClearFast(0, (void *)(base + 0x40), 0x30);
    if (*(void **)(base + 0xb8) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(base + 0xb8));
        *(u32 *)(base + 0xb8) = 0;
    }
    NNSi_FndFreeFromDefaultHeap(*(void **)(base + 0x38));
    *(u32 *)(base + 0x38) = 0;
}
