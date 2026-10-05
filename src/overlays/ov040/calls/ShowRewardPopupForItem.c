#include "nitro/types.h"

typedef struct RewardItemInfo {
    u8 pad_00[0x7d];
    u8 kind;
} RewardItemInfo;

typedef struct RewardItem {
    u8 pad_00[8];
    RewardItemInfo *info;
} RewardItem;

typedef struct RewardPopup {
    u8 pad_00[0xc];
    RewardItem *pendingItem;
    s32 timer;
} RewardPopup;

extern RewardPopup *data_ov040_020be284;
extern void func_ov007_020a1b28(RewardItem *item, s32 *outCode, u32 *outValue);
extern u32 func_ov040_020bdc44(u32 code);
extern void func_ov001_020788b8(s32 id, u16 value);

void ShowRewardPopupForItem(RewardItem *item)
{
    RewardPopup *popup = data_ov040_020be284;

    if (item->info->kind == 5) {
        if (item != popup->pendingItem) {
            s32 code;
            u32 value;
            u16 shortValue;
            s32 flagId;

            popup->pendingItem = item;
            func_ov007_020a1b28(item, &code, &value);
            shortValue = value;
            flagId = func_ov040_020bdc44(code);
            func_ov001_020788b8(flagId, shortValue);
        }
        popup->timer = 0;
    }
}




