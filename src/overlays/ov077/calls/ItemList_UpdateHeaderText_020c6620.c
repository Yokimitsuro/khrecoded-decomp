#include "nitro/types.h"

typedef struct CommandRecord {
    u8 pad_00[0x1e];
    s16 level;
} CommandRecord;

typedef struct ItemDef {
    s32 handle;
    s32 isRecord;
    u8 pad_08[0x18];
    s32 recordId;
    u8 pad_24[0x1c];
    const u16 *name;
    const u16 *description;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef struct ItemListMenu {
    u8 pad_0000[0x3c18];
    ItemStock *stocks[(0x4d84 - 0x3c18) / 4];
    s16 stockCount;
    s16 cursorIndex;
    u8 pad_4D88[0x11ea8 - 0x4d88];
    s32 recordPalette;
    s32 itemPalette;
    s32 defaultPalette;
    s32 currentPalette;
    void (*applyPalette)(void *target, int palette);
} ItemListMenu;

extern void *GetActiveRecordEntryOrNull(int index);
extern ItemStock *func_ov077_020c9dd4(ItemListMenu *menu, void *record);
extern CommandRecord *GetRecordSlotPair1Entry(s32 index);
extern void *func_ov039_020bc638(void);
extern void SetStatusHeaderMessage(const u16 *shortText, const u16 *longText, int kind, int value);

void ItemList_UpdateHeaderText_020c6620(ItemListMenu *menu)
{
    const u16 *name = NULL;
    const u16 *description = NULL;
    int level = 0;
    int palette = menu->defaultPalette;
    int index = menu->cursorIndex;

    if (index >= 0 && index < menu->stockCount) {
        ItemStock *stock = menu->stocks[index];
        ItemDef *def = stock->def;
        void *record = NULL;

        if (stock->recordIndex >= 0) {
            record = GetActiveRecordEntryOrNull((u16)stock->recordIndex);
        }
        if (record != NULL) {
            stock = func_ov077_020c9dd4(menu, record);
            palette = menu->recordPalette;
        } else if (def->isRecord == 0) {
            palette = menu->itemPalette;
        }
        description = def->description;
        name = def->name;
        if (def->handle < 0x90 && def->recordId != -1) {
            level = GetRecordSlotPair1Entry(stock->def->recordId)->level;
        }
    }
    if (menu->currentPalette != palette) {
        menu->currentPalette = palette;
        menu->applyPalette(func_ov039_020bc638(), palette);
    }
    SetStatusHeaderMessage(name, description, level > 0, (s16)level);
}

