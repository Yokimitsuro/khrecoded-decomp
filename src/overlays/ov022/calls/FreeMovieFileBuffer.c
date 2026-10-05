#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *buffer;
    u32 size;
    u32 fill;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7db4;

extern void MI_CpuCopy8(void *buffer, u32 fill, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void FreeMovieFileBuffer(void) {
    MI_CpuCopy8(data_ov022_020b7db4.buffer, data_ov022_020b7db4.fill, data_ov022_020b7db4.size);
    NNSi_FndFreeFromDefaultHeap(data_ov022_020b7db4.buffer);
}
