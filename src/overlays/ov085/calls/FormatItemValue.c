#include "nitro/types.h"

typedef struct ItemStatus {
    u8 pad_00[8];
    int value;
} ItemStatus;

typedef struct ItemSlot {
    u8 pad_00[8];
    ItemStatus *status;
} ItemSlot;

typedef struct ItemMenu {
    u8 pad_00[2];
    u8 useCatalog;
    u8 pad_03[0x5a49];
    ItemSlot *slots[1];
} ItemMenu;

extern void *GetItemMenuEntry(ItemMenu *menu, int index);
extern int GetItemSellPrice(void *entry);
extern int OS_SNPrintf_0202e094(char *dst, u32 len, const char *fmt, ...);
extern const char data_ov085_020c23bc[];

char *FormatItemValue(ItemMenu *menu, int index, char *buffer)
{
    int value;

    if (menu->useCatalog) {
        value = GetItemSellPrice(GetItemMenuEntry(menu, index));
    } else {
        value = menu->slots[index]->status->value;
    }
    OS_SNPrintf_0202e094(buffer, 0x2e, data_ov085_020c23bc, value);
    return buffer;
}
