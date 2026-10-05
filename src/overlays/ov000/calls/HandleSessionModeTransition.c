#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x667c];
    u32 sessionValue;
    u32 sessionReady;
} Panel;

extern u32 func_ov000_02063770(void);
extern u32 func_ov000_02063784(void);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

s32 HandleSessionModeTransition(Panel *panel)
{
    s32 result = -1;

    switch (func_ov000_02063770()) {
    case 0:
        break;
    case 1:
        SetPanelState(panel, 1, 0, 0);
        panel->sessionReady = 1;
        panel->sessionValue = func_ov000_02063784();
        StopSoundStreamAtIndex(0, 0x1e);
        result = 0xb;
        break;
    case 2:
        SetPanelState(panel, 1, 0, 0x10);
        result = 6;
        break;
    }
    return result;
}
