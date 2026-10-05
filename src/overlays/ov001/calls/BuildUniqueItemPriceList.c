#include "nitro/types.h"

typedef struct ShopState {
    u8 pad_000[0x109];
    u8 itemCount;
    u8 itemIds[0x16];
    u8 prices[0x16];
} ShopState;

extern ShopState *data_ov001_020a0490;
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern s32 GetShortTableValueOrDefault(s32 index);

void BuildUniqueItemPriceList(u16 *ids, int count)
{
    ShopState *shop = data_ov001_020a0490;
    int i;
    int j;

    shop->itemCount = 0;
    MI_CpuFill8(shop->itemIds, 0xff, 0x16);
    for (i = 0; i < count; i++) {
        BOOL found = FALSE;
        for (j = 0; j < shop->itemCount; j++) {
            if (shop->itemIds[j] == ids[i]) {
                found = TRUE;
                break;
            }
        }
        if (!found) {
            shop->itemIds[shop->itemCount] = ids[i];
            shop->itemCount++;
        }
    }
    MI_CpuFill8(shop->prices, 0x28, 0x16);
    AcquireRecordSlot(7, 1);
    for (i = 0; i < shop->itemCount; i++) {
        shop->prices[i] = GetShortTableValueOrDefault(shop->itemIds[i]);
    }
    ReleaseRecordSlot(7);
}
