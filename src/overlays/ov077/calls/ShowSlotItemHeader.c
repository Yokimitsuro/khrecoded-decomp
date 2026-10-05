#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
    u8 pad_2c6b[0x2db4 - 0x2c6b];
    u16 slotRecords[1];
} SaveData;

typedef struct {
    u8 pad_00[0x40];
    const u16 *name;
    const u16 *description;
} ItemDef;

typedef struct {
    ItemDef *def;
    u8 pad_04[8];
} ItemSlot;

typedef struct {
    u8 pad_00000[0x814];
    ItemSlot items[(0x11ff8 - 0x814) / 12];
    s32 slot;
} ItemMenu;

extern SaveData *data_0205fe0c;
extern void SetStatusHeaderText(const u16 *shortText, const u16 *longText);

static inline u32 GetSlotRecord(int slot)
{
    switch (slot) {
    case 0:
        return data_0205fe0c->slotRecords[0];
    case 1:
        return data_0205fe0c->slotRecords[1];
    default:
        if (slot >= 2 && slot < data_0205fe0c->extraSlotCount + 3) {
            return data_0205fe0c->slotRecords[slot];
        }
        return 0xffff;
    }
}

void ShowSlotItemHeader(ItemMenu *menu)
{
    u32 record = GetSlotRecord(menu->slot);

    if (record != 0xffff) {
        ItemDef *def = menu->items[record].def;
        SetStatusHeaderText(def->name, def->description);
        return;
    }
    SetStatusHeaderText(NULL, NULL);
}

