#include "nitro/types.h"

extern u32 ResetSceneSlots(void);
extern u32 func_ov001_02086d28(void);

u32 TryEnterState4(void)
{
    u32 result;

    result = func_ov001_02086d28();
    if (result == 0) {
        return 0xffffffff;
    }
    ResetSceneSlots();
    return 4;
}
