#include "nitro/types.h"

extern u32 ResetSceneSlots(void);
extern u32 StepResourceSlotLoading(void);

u32 TryEnterState4(void)
{
    u32 result;

    result = StepResourceSlotLoading();
    if (result == 0) {
        return 0xffffffff;
    }
    ResetSceneSlots();
    return 4;
}
