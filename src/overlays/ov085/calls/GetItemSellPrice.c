#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0xc];
    u32 basePrice;
} ItemInfo;

typedef struct ItemEntry {
    u8 pad_00[4];
    s16 recordId;
    u8 pad_06[2];
    ItemInfo *info;
} ItemEntry;

typedef struct RecordEntry {
    u16 rank : 2;
    u16 : 14;
    u16 active : 1;
    u16 level : 7;
} RecordEntry;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);
extern u16 data_ov085_020c22ea[];

int GetItemSellPrice(ItemEntry *entry)
{
    u32 price = entry->info->basePrice;

    if (entry->recordId >= 0) {
        RecordEntry record = *GetActiveRecordEntryOrNull((u16)entry->recordId);
        price += price * 10 / 300 * record.level * data_ov085_020c22ea[record.rank] / 10;
    }
    return price;
}
