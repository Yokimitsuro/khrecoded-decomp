#include "nitro/types.h"

typedef struct ShopInfo {
    int recordId;
    u8 pad_04[3];
    u8 stockLimit;
    u32 price;
} ShopInfo;

typedef struct OwnedEntry {
    u8 *count;
    u8 pad_04[4];
    ShopInfo *shop;
} OwnedEntry;

typedef struct CatalogEntry {
    u16 total;
    u16 used;
    s16 recordId;
} CatalogEntry;

typedef struct ItemMenu {
    u8 pad_00[2];
    u8 useCatalog;
    u8 pad_03[0x36a1];
    CatalogEntry *catalog[0x8ea];
    OwnedEntry *slots[1];
} ItemMenu;

extern u8 *data_0205fe0c;
extern BOOL CanAllocateRecordSlot(int index);

BOOL CanSelectItem(ItemMenu *menu, int index)
{
    if (menu->useCatalog) {
        CatalogEntry *entry = menu->catalog[(u16)index];

        if (entry->recordId >= 0) {
            if (entry->used != 0) {
                return FALSE;
            }
            return TRUE;
        }
        if (entry->total - entry->used <= 0) {
            return FALSE;
        }
        return TRUE;
    } else {
        BOOL result = FALSE;
        BOOL affordable = FALSE;
        BOOL inStock;
        OwnedEntry *slot = menu->slots[index];
        ShopInfo *shop = slot->shop;

        if (*(u32 *)(data_0205fe0c + 0x28d0) >= shop->price) {
            inStock = TRUE;

            if (shop->stockLimit != 0 && *slot->count >= shop->stockLimit) {
                inStock = FALSE;
            }
            if (inStock) {
                affordable = TRUE;
            }
        }
        if (affordable && CanAllocateRecordSlot(shop->recordId)) {
            result = TRUE;
        }
        return result;
    }
}
