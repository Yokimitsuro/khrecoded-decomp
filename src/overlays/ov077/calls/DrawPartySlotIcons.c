#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0x10];
    s32 iconIndex;
} ItemInfo;

typedef struct ItemSlotEntry {
    u8 pad_00[0x8];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct ItemScreen {
    u8 pad_000[0x48];
    u8 iconTable[0x80c - 0x48];
    ItemSlotEntry slots[1];
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

extern SaveState *data_0205fe0c;
extern void func_ov077_020c9f80(void *iconTable, u32 icon, u32 position, int flags);

static inline u16 GetPartySlot(int i)
{
    switch (i) {
    case 0:
        return data_0205fe0c->partySlots[0];
    case 1:
        return data_0205fe0c->partySlots[1];
    default:
        if (i >= 2 && i < data_0205fe0c->extraSlotCount + 3) {
            return data_0205fe0c->partySlots[i];
        }
        return 0xffff;
    }
}

void DrawPartySlotIcons(ItemScreen *screen, BOOL raised)
{
    int i;

    for (i = 0; i < 6; i++) {
        if (GetPartySlot(i) != 0xffff) {
            int dy = 8;
            int baseY;
            int y;
            int x;

            if (i != 1) {
                dy = 0;
            }
            if (raised) {
                baseY = -0x20;
            } else {
                baseY = 0;
            }
            y = baseY + 0x58 + dy;
            x = i * 16 + 0x28 + (i >= 2 ? 0x18 : 0);
            func_ov077_020c9f80(screen->iconTable,
                                ((u16)screen->slots[GetPartySlot(i)].info->iconIndex << 16) | 0x7fff,
                                (u16)(s16)x | ((s16)y << 16), 0);
        }
    }
}
