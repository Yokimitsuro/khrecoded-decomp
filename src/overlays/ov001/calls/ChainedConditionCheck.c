#include "nitro/types.h"

extern s32 GetRecordSlotEnabled(void);
extern s32 GetGroupMemberValueIfAny(void);

s32 ChainedConditionCheck(void)
{
    s32 result;

    result = GetRecordSlotEnabled();
    if (result == 0) {
        return 0;
    }
    result = GetGroupMemberValueIfAny();
    if (result == 0) {
        result = 0;
    }
    return result;
}
