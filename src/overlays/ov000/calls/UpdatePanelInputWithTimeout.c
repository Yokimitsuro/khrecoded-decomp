#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u16 inputState;
    u8 pad_0a[0x58 - 0xa];
    BOOL inputEnabled;
    u8 pad_5c[0x19c - 0x5c];
    BOOL active;
    u8 pad_1a0[0x66d0 - 0x1a0];
    u64 startTick;
} Panel;

extern u16 data_020604fc;
extern int FS_UnloadOverlayImage_0204f5f0(void *input);
extern u32 ReadHalfword(void *input);
extern s32 func_ov000_02061de8(Panel *panel, u32 buttons);
extern void HighlightPanelCursorLayer(Panel *panel);
extern u64 OS_GetTick(void);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

s32 UpdatePanelInputWithTimeout(Panel *panel)
{
    s32 result = -1;

    FS_UnloadOverlayImage_0204f5f0(&panel->inputState);
    if (panel->inputEnabled) {
        result = func_ov000_02061de8(panel, ReadHalfword(&panel->inputState));
    }
    if (!panel->active) {
        return result;
    }
    if (data_020604fc == 0) {
        panel->inputEnabled = TRUE;
    }
    HighlightPanelCursorLayer(panel);
    /* Idle timeout of 105 seconds */
    if (result == -1 && OS_GetTick() >= panel->startTick + 0x346fce2) {
        SetPanelState(panel, 1, 0x1e, 0);
        StopSoundStreamAtIndex(0, 0x1e);
        result = 0xc;
    }
    return result;
}
