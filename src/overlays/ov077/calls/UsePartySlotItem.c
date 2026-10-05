#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0x20];
    s32 category;
} ItemInfo;

typedef struct ItemSlotEntry {
    u16 unk_00;
    u16 count;
    u8 pad_04[0x4];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct ItemScreen {
    u8 pad_00000[0x18];
    s32 busy;
    u8 pad_0001c[0x80c - 0x1c];
    ItemSlotEntry slots[0x5d0];
    u8 pad_4dcc[0x7fb0 - 0x4dcc];
    s32 windowState;
    u8 pad_7fb4[0x11ff8 - 0x7fb4];
    s32 tab;
} ItemScreen;

typedef struct SaveState {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 partySlots[8];
} SaveState;

typedef struct PartyRefreshArgs {
    u32 words[6];
} PartyRefreshArgs;

extern SaveState *data_0205fe0c;
extern const PartyRefreshArgs data_ov077_020ca128;
extern void PlaySoundEffect(int id, int channel);
extern void func_ov073_020c1ed4(SaveState *save, const PartyRefreshArgs *args);
extern void func_ov077_020c5a6c(ItemScreen *screen, int slot);
extern void func_ov073_020c2cc4(int page, int cursor);
extern void ShowSlotHeaderMessage(ItemScreen *screen);

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

static inline void SetPartySlot(int i, u16 value)
{
    switch (i) {
    case 0:
        data_0205fe0c->partySlots[0] = value;
        break;
    case 1:
        data_0205fe0c->partySlots[1] = value;
        break;
    default:
        if (i >= 2 && i < data_0205fe0c->extraSlotCount + 3) {
            PartyRefreshArgs args = data_ov077_020ca128;
            data_0205fe0c->partySlots[i] = value;
            func_ov073_020c1ed4(data_0205fe0c, &args);
        }
        break;
    }
}

void UsePartySlotItem(ItemScreen *screen)
{
    ItemSlotEntry *entry;
    u16 index;

    if (screen->busy != 0) {
        return;
    }
    if (screen->windowState != 4) {
        return;
    }
    if (screen->tab >= 2) {
        index = GetPartySlot(screen->tab);
        if (index == 0xffff) {
            return;
        }
        entry = &screen->slots[index];
        entry->count--;
        PlaySoundEffect(1, 6);
        SetPartySlot(screen->tab, 0xffff);
        func_ov077_020c5a6c(screen, screen->tab);
        func_ov073_020c1ed4(data_0205fe0c, NULL);
        func_ov073_020c2cc4(2, entry->info->category);
        ShowSlotHeaderMessage(screen);
    } else {
        PlaySoundEffect(1, 4);
    }
}
