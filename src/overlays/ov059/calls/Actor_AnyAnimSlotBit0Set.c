#include "nitro/types.h"

typedef struct {
    u8 data[0x230];
} AnimSlot;

typedef struct {
    u8 pad_000[0x9d4];
    AnimSlot slots[2];
} Actor;

extern BOOL IsBit0Set(AnimSlot *slot);

BOOL Actor_AnyAnimSlotBit0Set(Actor *actor)
{
    BOOL found = FALSE;
    int i;

    for (i = 0; i < 2; i++) {
        if (IsBit0Set(&actor->slots[i])) {
            found = TRUE;
            break;
        }
    }
    return found;
}
