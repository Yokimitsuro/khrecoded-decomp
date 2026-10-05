#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 FindFirstActiveStageEvent(void);

s32 ForwardToActiveServiceWithResult(void)
{
    s32 result;

    if (data_ov001_0209f2e8 != -1) {
        result = FindFirstActiveStageEvent();
        return result;
    }
    return 0;
}
