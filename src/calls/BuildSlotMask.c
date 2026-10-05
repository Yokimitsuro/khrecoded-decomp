#include "nitro/types.h"

/* Bit set when a slot passes its threshold. */
u32 BuildSlotMask(int slotList, int offset)
{
    u32 mask = 0;
    u32 i = 0;

    do {
        if (((s16 *)slotList)[i + 1] >= 0) {
            int *slot = ((int **)slotList)[i + 3];
            if (*slot >= (int)((u32)*(u16 *)(slot[2] + 4) * 0x1000 - offset)) {
                mask |= (u16)(1 << i);
            }
        }
        i = i + 1;
    } while ((int)i < 5);

    return mask;
}
