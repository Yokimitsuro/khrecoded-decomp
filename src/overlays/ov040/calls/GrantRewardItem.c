#include "nitro/types.h"

typedef struct StackSlot {
    s16 id;
    u8 pad_02[2];
    u8 count;
    u8 maxCount;
    u8 pad_06[6];
} StackSlot;

typedef struct RewardPopup {
    u8 pad_00[0xc];
    void *pendingItem;
    s32 timer;
} RewardPopup;

extern RewardPopup *data_ov040_020be284;
extern u32 func_ov040_020bdc44(u32 code);
extern u32 RewardFlagToItemCode(u32 flagId);
extern int AddToStackSlot(const StackSlot *request);
extern void func_ov001_02078360(int a, int b);
extern int func_ov001_0207865c(void);
extern void func_02050394(StackSlot *replaced, StackSlot *request, int slot);
extern void func_ov001_020785c0(s32 slotId, u16 value);
extern void func_ov001_02078500(s32 slotId, u16 slot, u16 amount);
extern void func_ov001_020788b8(s32 id, u16 value);

BOOL GrantRewardItem(void *unused, u32 *code, u32 *count)
{
    RewardPopup *popup = data_ov040_020be284;
    StackSlot request;
    StackSlot replaced;
    BOOL replacedSlot;
    int slot;

    request.count = *count;
    request.maxCount = 99;
    replacedSlot = FALSE;
    request.id = func_ov040_020bdc44(*code);
    if (request.id == -1) {
        return replacedSlot;
    }
    slot = AddToStackSlot(&request);
    if (slot < 0) {
        replacedSlot = TRUE;
        func_ov001_02078360(1, 1);
        func_02050394(&replaced, &request, func_ov001_0207865c());
        func_ov001_020785c0(request.id, request.count);
        *code = RewardFlagToItemCode(replaced.id);
        *count = replaced.count;
    } else {
        func_ov001_02078500(request.id, slot, request.count);
    }
    func_ov001_020788b8(*code, 0);
    popup->pendingItem = NULL;
    return replacedSlot;
}

