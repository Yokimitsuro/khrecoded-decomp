#include "nitro/types.h"

extern s32 data_ov001_0209f2e8;
extern s32 func_ov001_0209c968(void);

s32 ForwardToActiveServiceWithResult(void)
{
    s32 result;

    if (data_ov001_0209f2e8 != -1) {
        result = func_ov001_0209c968();
        return result;
    }
    return 0;
}
