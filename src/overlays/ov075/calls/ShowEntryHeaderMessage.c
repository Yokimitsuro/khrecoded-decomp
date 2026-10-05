#include "nitro/types.h"

typedef struct NamedItem {
    u8 pad_00[0x40];
    const u16 *name;
    const u16 *description;
} NamedItem;

typedef struct ItemRow {
    NamedItem *item;
    u8 pad_04[8];
} ItemRow;

typedef struct RecordInfo {
    u8 pad_00[0x28];
    const u16 *name;
    const u16 *description;
} RecordInfo;

typedef struct ListEntry {
    u8 pad_00[2];
    u8 kind;
    u8 pad_03;
    s16 rowIndex;
    u16 slot;
    u8 isLocked;
} ListEntry;

typedef struct SlotTable {
    u8 pad_0000[0x24dc];
    s16 recordIds[1];
} SlotTable;

typedef struct MenuContent {
    u8 pad_0000[0x800];
    ItemRow rows[(0x4e5c - 0x800) / 0xc];
    u8 messageTable[4];
} MenuContent;

typedef struct MatrixMenu {
    u8 pad_00000[0x84];
    MenuContent content;
    u8 pad_after[0x12dd0 - 0x84 - sizeof(MenuContent)];
    SlotTable *slots;
} MatrixMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c67];
    u8 hintsEnabled;
} SaveData;

extern SaveData *data_0205fe0c;
extern u16 data_ov075_020d1878[];

extern void *func_ov027_020ba2c8(void *table, int index);
extern RecordInfo *GetRecordSlotPair1Entry(s32 index);
extern u16 GetByteCounterOrDefault(int index);
extern void SetStatusHeaderMessage(const u16 *shortText, const u16 *longText, int kind, int value);

void ShowEntryHeaderMessage(MatrixMenu *menu, ListEntry *entry)
{
    MenuContent *content = &menu->content;
    const u16 *description;
    int kind;
    u16 count;
    const u16 *name;
    int messageId;
    int recordId;
    SlotTable *slots;

    kind = 0;
    description = NULL;
    count = 0;
    name = NULL;
    if (entry == NULL) {
        goto done;
    }
    if (entry->rowIndex >= 0) {
        NamedItem *item = content->rows[entry->rowIndex].item;

        name = item->name;
        description = item->description;
        goto done;
    }
    slots = menu->slots;
    if (entry->kind == 6) {
        recordId = slots->recordIds[entry->slot];
    } else {
        recordId = -1;
    }
    if (recordId >= 0) {
        RecordInfo *record = GetRecordSlotPair1Entry(recordId);

        if (entry->kind == 6 && entry->isLocked) {
            name = func_ov027_020ba2c8(content->messageTable, 0x1a);
            description = data_ov075_020d1878;
        } else {
            name = record->name;
            description = record->description;
        }
        goto done;
    }
    messageId = -1;
    switch (entry->kind) {
    case 9:
        messageId = 6;
        break;
    case 10:
        messageId = 8;
        break;
    case 11:
        messageId = 10;
        break;
    case 12:
        messageId = 12;
        break;
    case 13:
        messageId = 14;
        break;
    case 3:
        messageId = 16;
        break;
    case 7:
        messageId = 20;
        break;
    case 8:
        messageId = 18;
        break;
    case 4:
        messageId = 22;
        kind = 2;
        count = GetByteCounterOrDefault(0x160);
        break;
    case 5:
        kind = 3;
        messageId = 24;
        count = GetByteCounterOrDefault(0x161);
        break;
    }
    if (messageId >= 0) {
        name = func_ov027_020ba2c8(content->messageTable, messageId);
        description = func_ov027_020ba2c8(content->messageTable,
                                          (entry->kind == 3 && data_0205fe0c->hintsEnabled == 0) ? 0x60 : messageId + 1);
    }
done:
    SetStatusHeaderMessage(name, description, kind, (s16)count);
}
