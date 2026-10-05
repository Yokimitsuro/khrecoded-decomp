#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0x8];
    s32 maxCount;
    u8 pad_0c[0x14];
    s32 category;
    s32 kind;
} ItemInfo;

typedef struct ItemSlotEntry {
    u8 pad_00[0x8];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct DigitSprite {
    s32 visible;
    s32 unk_04;
    s32 value;
    u8 pad_0c[0xC];
} DigitSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x80c];
    ItemSlotEntry slots[0x5d0];
    u8 pad_4dcc[0x11edc - 0x4dcc];
    DigitSprite digits[7];
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2db4];
    u16 selectedSlot;
    u8 pad_2db6[0x2de0 - 0x2db6];
    u16 itemCounts[1];
} SaveState;

extern SaveState *data_0205fe0c;

void UpdateItemCountDigits(ItemScreen *screen)
{
    ItemInfo *info;
    int count;
    int maxCount;
    int gauge;
    int i;

    for (i = 0; i <= 6; i++) {
        screen->digits[i].visible = 0;
    }
    info = screen->slots[data_0205fe0c->selectedSlot].info;
    if (info->kind == 5) {
        screen->digits[6].visible = 1;
        return;
    }
    count = data_0205fe0c->itemCounts[info->category];
    maxCount = info->maxCount;
    screen->digits[0].visible = (count / 1000 != 0);
    screen->digits[0].value = count / 1000;
    screen->digits[1].visible = (count / 100 != 0);
    screen->digits[1].value = count / 100 % 10;
    screen->digits[2].visible = (count / 10 != 0);
    screen->digits[2].value = count / 10 % 10;
    screen->digits[3].visible = 1;
    screen->digits[3].value = count % 10;
    screen->digits[5].visible = 1;
    screen->digits[4].visible = 1;
    gauge = 0;
    if (count > 0) {
        gauge = (count * 0xd000 / maxCount >> 12) + 1;
    }
    if (gauge >= 14) {
        gauge = 14;
    }
    screen->digits[4].value = gauge;
}
