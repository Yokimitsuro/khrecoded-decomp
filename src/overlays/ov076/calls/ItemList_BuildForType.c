#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0x4];
    u32 type;
    u8 pad_08[0x10];
    u16 sortKey;
} ItemInfo;

typedef struct ItemEntry {
    u16 count;
    u8 pad_02[0x6];
    ItemInfo *info;
} ItemEntry;

typedef struct ItemScreen {
    ItemEntry entries[0x200];
    ItemEntry records[600];
    ItemEntry *list[0x458];
    u16 listCount;
    u8 listReady;
    u8 pad_4583;
    u32 typeMask;
} ItemScreen;

extern void ItemList_BuildStock(ItemScreen *screen);
extern void *GetActiveRecordEntryOrNull(u16 index);
extern void func_02021ca8(void *base, u32 count, u32 size, void *compare);
extern int ItemList_CompareStock(const void *a, const void *b);

void ItemList_BuildForType(ItemScreen *screen, u32 type)
{
    s16 j;
    ItemEntry *record;
    s16 i;
    ItemEntry *entry;
    BOOL all;
    ItemEntry **out = screen->list;

    if (!screen->listReady) {
        ItemList_BuildStock(screen);
    }
    screen->listCount = 0;
    if (screen->typeMask & (1 << type)) {
        all = TRUE;
        if (type != 11) {
            all = FALSE;
        }
        if (all || (type != 3 && type != 2)) {
            entry = screen->entries;
            for (i = 0; i < 0x200; i++, entry++) {
                if ((i < 0 || i > 0x7f) && entry->count != 0 && entry->info->sortKey < 9999 &&
                    (all || type == entry->info->type)) {
                    *out++ = entry;
                    screen->listCount++;
                }
            }
        }
        if (all || type == 2 || type == 3) {
            record = screen->records;
            for (j = 0; j < 600; j++, record++) {
                if (GetActiveRecordEntryOrNull(j) != NULL && record->info->sortKey < 9999 &&
                    record->count != 0 && (all || type == record->info->type)) {
                    *out++ = record;
                    screen->listCount++;
                }
            }
        }
        func_02021ca8(screen->list, screen->listCount, 4, ItemList_CompareStock);
    }
}
