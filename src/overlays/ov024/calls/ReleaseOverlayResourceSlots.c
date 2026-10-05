#include "nitro/types.h"

extern void *data_ov024_020b754c[6];
extern void NNSi_FndFreeFromDefaultHeap(void *memory);

void ReleaseOverlayResourceSlots(void)
{
    int slotIndex = 0;
    do {
        if (data_ov024_020b754c[slotIndex] != NULL) {
            NNSi_FndFreeFromDefaultHeap(data_ov024_020b754c[slotIndex]);
            data_ov024_020b754c[slotIndex] = NULL;
        }
        slotIndex++;
    } while (slotIndex < 6);
}
