#include "nitro/types.h"

typedef struct EffectSlot {
    u32 flags;
    int timer;
    u8 pad_008[0x11c - 0x8];
    u8 baseSet[0x148 - 0x11c];
    u8 extraSet[0x1cc - 0x148];
    u8 specialSet[0x230 - 0x1cc];
} EffectSlot;

typedef struct EffectOwner {
    u8 pad_000[0x9d4];
    EffectSlot slots[1];
} EffectOwner;

extern void func_ov021_020a9b94(EffectSlot *slot, void *set, int index, int arg3, int arg4);

void EffectSlot_StartByKind(EffectOwner *owner, int slotIndex, int kind, int arg) {
    int index;
    void *set = NULL;
    EffectSlot *slot = &owner->slots[slotIndex];

    if (slot->flags & 1) {
        slot->timer = 0;
        slot->flags &= ~0x400;
        if (kind == 11) {
            set = slot->specialSet;
            index = 0;
        } else if (kind == 12) {
            set = slot->specialSet;
            index = 1;
        } else if (kind == 14) {
            set = slot->specialSet;
            index = 2;
        } else if (kind == 15) {
            set = slot->specialSet;
            index = 3;
        } else if (kind == 10) {
            set = slot->specialSet;
            index = 4;
        } else if (kind == 1) {
            set = slot->specialSet;
            index = 5;
        } else if (kind < 13) {
            set = slot->baseSet;
            index = kind;
        } else if (kind >= 13 && kind < 18) {
            set = slot->extraSet;
            index = kind - 13;
        }
        func_ov021_020a9b94(slot, set, index, 0, arg);
    }
}
