#include "nitro/types.h"

extern u32 func_ov040_020bdc44(u32 code);
extern int GetPlayerFlagRecord(int index);

BOOL IsRewardSlotUnclaimed(void *unused, u32 code)
{
    int i;
    BOOL result = TRUE;
    int flagId = func_ov040_020bdc44(code);

    for (i = 0; i < 8; i++) {
        s16 value = *(s16 *)GetPlayerFlagRecord(i);
        if (value == flagId || value == -1) {
            result = FALSE;
            break;
        }
    }
    return result;
}

