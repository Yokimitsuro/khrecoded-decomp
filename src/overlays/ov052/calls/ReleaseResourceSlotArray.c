#include "nitro/types.h"

extern void ReleaseResourceAndDetach(u8 *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

/* Releases four resource slots and frees the array */
void ReleaseResourceSlotArray(int entity)
{
    int slotIndex;

    for (slotIndex = 0; slotIndex < 4; slotIndex++) {
        ReleaseResourceAndDetach(*(u8 **)(entity + 0x106c) + slotIndex * 0x104);
    }
    NNSi_FndFreeFromDefaultHeap(*(u8 **)(entity + 0x106c));
}
