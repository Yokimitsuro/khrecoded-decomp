#include "nitro/types.h"

typedef struct RecordEntry RecordEntry;

typedef struct {
    u8 pad_00[0x1e];
    s16 stock;
} SlotPair1Entry;

typedef struct {
    s32 id;
    s32 kind;
    u8 pad_08[0x18];
    s32 pairIndex;
    u8 pad_24[0x1c];
    const u16 *title;
    const u16 *description;
} ItemDef;

typedef struct {
    u8 pad_00[4];
    s16 recordIndex;
    u16 pad_06;
    ItemDef *def;
} ItemSlot;

typedef void (*ScreenCallback)(u32 context, u32 screen);

typedef struct {
    u8 pad_00000[0x3c18];
    ItemSlot *slots[0x45b];
    s16 slotCount;
    s16 cursor;
    u8 pad_4d88[0x11ea8 - 0x4d88];
    u32 recordScreen;
    u32 kindZeroScreen;
    u32 defaultScreen;
    u32 currentScreen;
    ScreenCallback onScreenChange;
} ItemPicker;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern ItemSlot *func_ov075_020d0f54(ItemPicker *picker, RecordEntry *record);
extern SlotPair1Entry *GetRecordSlotPair1Entry(s32 index);
extern u32 func_ov039_020bc638(void);
extern void SetStatusHeaderMessage(const u16 *shortText, const u16 *longText, int kind, s16 value);

void UpdateItemDescription(ItemPicker *picker)
{
    const u16 *title;
    const u16 *description;
    int stock;
    u32 screen;
    int cursor;
    ItemSlot *slot;
    ItemDef *def;
    RecordEntry *record;

    title = NULL;
    description = NULL;
    stock = 0;
    screen = picker->defaultScreen;
    cursor = picker->cursor;

    if (cursor >= 0 && cursor < picker->slotCount) {
        slot = picker->slots[cursor];
        def = slot->def;
        record = NULL;
        if (slot->recordIndex >= 0) {
            record = GetActiveRecordEntryOrNull((u16)slot->recordIndex);
        }
        if (record != NULL) {
            slot = func_ov075_020d0f54(picker, record);
            screen = picker->recordScreen;
        } else if (def->kind == 0) {
            screen = picker->kindZeroScreen;
        }
        title = def->title;
        description = def->description;
        if (def->id < 0x90 && def->pairIndex != -1) {
            stock = GetRecordSlotPair1Entry(slot->def->pairIndex)->stock;
        }
    }
    if (picker->currentScreen != screen) {
        picker->currentScreen = screen;
        picker->onScreenChange(func_ov039_020bc638(), screen);
    }
    SetStatusHeaderMessage(title, description, stock > 0, stock);
}
