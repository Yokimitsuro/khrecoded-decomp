#include "nitro/types.h"

typedef struct SlotGroups {
    u8 pad_000[0x1d4];
    u8 recordSlots[22][16];
    u8 alphaOffsets[22][16];
    u8 counts[22];
    u8 alpha;
    u8 mode : 2;
    u8 flags_b2 : 6;
} SlotGroups;

extern void func_0204f18c(void *manager, int recordIndex, u8 alpha);
extern void Slot_SetMode2Bit(void *manager, int recordIndex, int mode);

void ApplyGroupSlotsAlpha(void *manager, SlotGroups *groups, int group, BOOL dimmed)
{
    int i;

    for (i = 0; i < groups->counts[group]; i++) {
        int alpha = groups->alpha - groups->alphaOffsets[group][i];
        int slot = groups->recordSlots[group][i];
        if (!dimmed) {
            func_0204f18c(manager, slot, alpha);
            Slot_SetMode2Bit(manager, slot, groups->mode);
        } else {
            alpha -= 100;
            if (alpha < 0) {
                alpha = 0;
            }
            func_0204f18c(manager, slot, alpha);
            Slot_SetMode2Bit(manager, slot, 0);
        }
    }
}
