#include "nitro/types.h"

extern s32 func_ov001_02091ad0(void);
extern s32 GetGroupMemberValueIfAny(void);

s32 ChainedConditionCheck(void)
{
    s32 result;

    result = func_ov001_02091ad0();
    if (result == 0) {
        return 0;
    }
    result = GetGroupMemberValueIfAny();
    if (result == 0) {
        result = 0;
    }
    return result;
}
