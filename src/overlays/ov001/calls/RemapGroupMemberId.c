#include "nitro/types.h"

extern const s8 data_ov001_020a03ac[];
extern int func_ov001_020644b0(void);
extern s32 func_ov032_020bb828(void);
extern BOOL IsContextSlotEnabled(int groupId);
extern u32 GetGroupIndexedValue(u32 index);

u32 RemapGroupMemberId(u32 memberId, int groupId, BOOL skipLookup)
{
    BOOL inSpecialScene = (func_ov001_020644b0() == 900) ? TRUE : FALSE;

    if (inSpecialScene) {
        u8 available = TRUE;
        BOOL groupValid = TRUE;
        if (!skipLookup) {
            available = func_ov032_020bb828();
            if (groupId != 0xffff) {
                groupValid = IsContextSlotEnabled(groupId);
            }
            memberId = GetGroupIndexedValue(memberId);
        }
        if (groupValid && available && memberId < 0x46) {
            s8 remapped = data_ov001_020a03ac[memberId];
            if (remapped < 0) {
                remapped = memberId + 0x46;
            }
            memberId = (u16)remapped;
        }
    }
    return memberId;
}
