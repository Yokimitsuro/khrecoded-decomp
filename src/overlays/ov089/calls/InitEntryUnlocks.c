#include "nitro/types.h"

typedef struct {
    int index;
    u8 model[0x104];
} EntryModel;

typedef struct {
    EntryModel entries[7];
    u8 pad_738[0xc];
    int entryCount;
    int cursor;
    u8 pad_74c[0x1bc];
    u8 unlockedMask;
} Ov089Menu;

typedef struct {
    u32 ids[6];
} UnlockFlagList;

extern UnlockFlagList data_ov089_020c0540;

extern BOOL func_ov001_020645c8(u32 flagId);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern int *func_01ffb2f8(void *model, int track, int value);
extern void RefreshEntryCaption(Ov089Menu *menu, BOOL playSound);

void InitEntryUnlocks(Ov089Menu *menu)
{
    UnlockFlagList flags = data_ov089_020c0540;
    int i;
    int firstLocked;

    firstLocked = -1;
    for (i = 0; i < 6; i++) {
        if (func_ov001_020645c8(flags.ids[i])) {
            menu->unlockedMask |= (u8)(1 << i);
        } else if (firstLocked == -1) {
            firstLocked = i;
        }
    }
    if (ReadSessionPackedBits(0x1a00, 2) == 0 && func_ov001_020645c8(0xa12)) {
        menu->unlockedMask |= 0x40;
    }
    if (ReadSessionPackedBits(0x3700, 3) == 7) {
        firstLocked = func_ov001_020645c8(0xa12) ? 0 : 6;
    } else if (firstLocked == -1) {
        firstLocked = 6;
    }
    for (i = 0; i < menu->entryCount; i++) {
        if (firstLocked == menu->entries[i].index) {
            menu->cursor = i;
        }
        if (menu->unlockedMask & (1 << menu->entries[i].index)) {
            func_01ffb2f8(menu->entries[i].model, 3, 0x1000);
        }
    }
    RefreshEntryCaption(menu, FALSE);
}
