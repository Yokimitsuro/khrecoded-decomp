#include "nitro/types.h"

typedef struct SlotPool {
    u32 *usedMasks;
    u8 pad_004[0x208];
    s16 capacity;
} SlotPool;

extern SlotPool *data_ov001_020a0484;

extern int func_0200d5a0(u32 mask);

int FindFreeEffectSlot(int kind)
{
    BOOL isShared = kind >= 6;
    u32 *mask;
    int base;
    int bit;

    if (isShared) {
        base = 0;
        mask = data_ov001_020a0484->usedMasks;
    } else {
        base = 0x20;
        mask = data_ov001_020a0484->usedMasks + 1;
    }
    for (;;) {
        bit = func_0200d5a0(*mask);
        if (bit < 0x20) {
            bit += base;
            if (isShared) {
                if (bit >= 0x20) {
                    return -1;
                }
            } else if (bit >= data_ov001_020a0484->capacity) {
                return -1;
            }
            return bit;
        }
        mask++;
        base += 0x20;
    }
}
