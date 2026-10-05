#include "nitro/types.h"

extern u32 data_ov038_020bd164;
extern void SetBrightnessAndSyncMain(s32 value);
extern void SetSecondaryBrightness(s32 value);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);
extern void ResetOv038ExitState(u32 mode);

u32 AdvanceOv038ExitTimer(void)
{
    u32 context;
    s32 tick;

    context = data_ov038_020bd164;
    tick = *(s32 *)(context + 0xd0a8);
    SetBrightnessAndSyncMain(-tick);
    SetSecondaryBrightness(-tick);
    if (*(s32 *)(context + 0xd0a8) == 0) {
        StopSoundStreamAtIndex(0, 0x10);
    }
    tick = *(s32 *)(context + 0xd0a8) + 1;
    *(s32 *)(context + 0xd0a8) = tick;
    if (0x10 < tick) {
        ResetOv038ExitState(4);
    }
    return 0;
}
