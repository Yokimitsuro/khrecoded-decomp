#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66d8];
    u32 busy;
} Panel;

extern int IsSoundStreamActive(int flag);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);

u32 TryEnterPanelState(Panel *panel)
{
    u32 result = 0xffffffff;

    if (IsSoundStreamActive(1) == 0) {
        panel->busy = 1;
        SetPanelState(panel, 1, 0, 0);
        result = 0xc;
    }
    return result;
}
