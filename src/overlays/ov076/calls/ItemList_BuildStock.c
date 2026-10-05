#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct ItemDef {
    u32 handle;
    u32 category;
    u8 pad_08[0x10];
    u16 sortKey;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

typedef struct ItemList {
    ItemStock stocks[0x458];
    u8 pad_3420[0x4580 - 0x3420];
    u16 filteredCount;
    u8 ready;
    u8 pad_4583;
    u32 categoryMask;
} ItemList;

typedef struct SaveData {
    u8 pad_0000[0x28d4];
    s8 chapter;
    u8 pad_28D5[3];
    u8 itemCounts[0x200];
    u8 pad_2AD8[0x2c6d - 0x2ad8];
    s8 equippedSlots[200];
    u8 pad_2D35[0x2d84 - 0x2d35];
    u16 slotHandles[16];
    u8 pad_2DA4[0x10];
    u16 extraHandleA;
    u16 extraHandleB;
    u16 extraHandles[4];
    s32 slotStock[8];
} SaveData;

extern SaveData *data_0205fe0c;

extern ItemDef *GetRecordSlotPair0Entry(int index);
extern int ReadGlobalPackedBits(int bitIndex, int bitCount);
extern RecordEntry *GetActiveRecordEntryOrNull(int index);

static inline BOOL IsChapterItemAvailable(int index)
{
    s8 chapter = data_0205fe0c->chapter;
    int progress = ReadGlobalPackedBits(0x1a00, 2);

    switch (index) {
    case 0x160:
    case 0x161:
    case 0x178:
    case 0x179:
    case 0x17a:
    case 0x17b:
    case 0x17c:
    case 0x17d:
    case 0x17e:
    case 0x17f:
    case 0x180:
    case 0x181:
    case 0x182:
    case 0x183:
    case 0x184:
    case 0x185:
    case 0x186:
    case 0x19c:
    case 0x19d:
    case 0x19e:
    case 0x19f:
    case 0x1a0:
    case 0x1a1:
    case 0x1a2:
    case 0x1a3:
    case 0x1a4:
    case 0x1a5:
    case 0x1a6:
    case 0x1a7:
    case 0x1a8:
    case 0x1a9:
    case 0x1aa:
    case 0x1ab:
    case 0x1ac:
    case 0x1ad:
        return TRUE;
    case 0x164:
        return chapter == 1 && progress < 2;
    case 0x168:
    case 0x169:
    case 0x16a:
    case 0x16b:
    case 0x16c:
    case 0x16d:
    case 0x16e:
    case 0x16f:
    case 0x170:
    case 0x171:
    case 0x172:
    case 0x173:
    case 0x174:
    case 0x175:
    case 0x176:
    case 0x177:
        return chapter == 2 && progress < 2;
    case 0x188:
        return chapter == 5 && progress < 2;
    case 0x18c:
    case 0x18d:
    case 0x18e:
    case 0x18f:
    case 0x190:
    case 0x191:
    case 0x192:
    case 0x194:
        return chapter == 7 && progress < 2;
    }
    return FALSE;
}

void ItemList_BuildStock(ItemList *list)
{
    ItemStock *stock = list->stocks;
    u8 *count = data_0205fe0c->itemCounts;
    s8 *equipped = data_0205fe0c->equippedSlots;
    s16 i;
    RecordEntry *record;
    int handle;
    int pair;
    u16 slotHandle;

    for (i = 0; i < 0x200; i++, stock++, count++) {
        stock->def = GetRecordSlotPair0Entry(i);
        if ((i < 0 || i > 0x7f) && *count != 0 && stock->def->sortKey < 9999) {
            if (stock->def->category != 10 || IsChapterItemAvailable(i)) {
                list->categoryMask |= 1 << stock->def->category;
                stock->total = *count;
                stock->used = 0;
            }
        }
        stock->recordIndex = -1;
    }

    for (i = 0; i < 600; i++, stock++) {
        record = GetActiveRecordEntryOrNull((u16)i);
        stock->total = 1;
        stock->used = 0;
        stock->recordIndex = i;
        if (record != NULL) {
            stock->def = GetRecordSlotPair0Entry((u8)record->category);
        } else {
            stock->def = NULL;
        }
        if (record != NULL && stock->def->sortKey < 9999) {
            list->categoryMask |= 1 << stock->def->category;
            list->stocks[stock->def->handle].total++;
        }
    }

    for (i = 0; i < 200; i++, equipped++) {
        if (*equipped >= 0) {
            list->stocks[*equipped + 0x90].used++;
        }
    }

    for (i = 0; i < 8; i++) {
        for (pair = 0; pair < 2; pair++) {
            slotHandle = data_0205fe0c->slotHandles[i * 2 + pair];
            if (slotHandle != 0xffff) {
                if (slotHandle < 0x200) {
                    list->stocks[slotHandle].used += (u16)data_0205fe0c->slotStock[i];
                } else {
                    handle = list->stocks[slotHandle].def->handle;
                    list->stocks[slotHandle].used++;
                    list->stocks[handle].used++;
                }
            }
        }
    }

    slotHandle = data_0205fe0c->extraHandleA;
    if (slotHandle != 0xffff) {
        list->stocks[slotHandle].used++;
    }
    slotHandle = data_0205fe0c->extraHandleB;
    if (slotHandle != 0xffff) {
        list->stocks[slotHandle].used++;
    }
    for (i = 0; i < 4; i++) {
        slotHandle = data_0205fe0c->extraHandles[i];
        if (slotHandle != 0xffff) {
            list->stocks[slotHandle].used++;
        }
    }

    list->categoryMask |= (list->categoryMask != 0) << 11;
    list->ready = 1;
}
