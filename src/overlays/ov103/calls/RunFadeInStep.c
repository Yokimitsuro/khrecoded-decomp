#include "nitro/types.h"

typedef struct {
    s32 selection;
    s32 brightness;
    u8 pad_0008[0xCB88 - 8];
    s32 phase;
    s32 step;
    s32 timer;
} Ov103State;

#define REG_MASTER_BRIGHT_MAIN ((vu16 *)0x0400006C)
#define REG_MASTER_BRIGHT_SUB ((vu16 *)0x0400106C)

extern BOOL IsStatePhase3(void);
extern int GXx_GetMasterBrightness_(vu16 *reg);
extern void GXx_SetMasterBrightness_(vu16 *reg, int value);
extern void SetScenePhase(s32 phase, Ov103State *state);
extern void RefreshRowHighlights(Ov103State *state);
extern void InitSlotPool_020bf688(Ov103State *state);

void RunFadeInStep(Ov103State *state)
{
    if (!IsStatePhase3()) {
        state->brightness = GXx_GetMasterBrightness_(REG_MASTER_BRIGHT_MAIN);
    } else {
        state->brightness++;
        if (state->brightness >= 0) {
            state->brightness = 0;
        }
        if (state->timer == 0) {
            state->brightness = -16;
        }
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_MAIN, state->brightness);
        GXx_SetMasterBrightness_(REG_MASTER_BRIGHT_SUB, state->brightness);
        state->timer++;
    }
    if (state->brightness == 0) {
        SetScenePhase(3, state);
    }
    RefreshRowHighlights(state);
    InitSlotPool_020bf688(state);
}
