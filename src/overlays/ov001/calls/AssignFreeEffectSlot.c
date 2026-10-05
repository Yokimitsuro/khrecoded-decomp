#include "nitro/types.h"

typedef struct EffectSlot {
    u8 pad_00[4];
    s16 id;
    u8 pad_06[0x26];
} EffectSlot;

typedef struct EffectOwner {
    u8 pad_000[0x5f8];
    EffectSlot slots[6];
} EffectOwner;

extern BOOL SetupStreamSlot(EffectOwner *owner, EffectSlot *slot, int a, int b, int c, int d, int e);

void AssignFreeEffectSlot(EffectOwner *owner, int a, int b, int c, int d, int e)
{
    int i = 0;
    EffectSlot *slots = owner->slots;

    for (; i < 6; i++) {
        if (slots[i].id == -1 && SetupStreamSlot(owner, &slots[i], a, b, c, d, e)) {
            return;
        }
    }
}
