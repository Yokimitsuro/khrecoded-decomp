#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern u8 *data_ov015_0207e964;

void FreePanelBuffers(void) {
    int i;

    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov015_0207e964 + 0x94));
    i = 0;
    do {
        NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov015_0207e964 + i * 4 + 0x98));
        i = i + 1;
    } while (i < 4);
    NNSi_FndFreeFromDefaultHeap(data_ov015_0207e964);
}
