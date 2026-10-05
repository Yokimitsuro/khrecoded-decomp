#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x1344];
    void (*exitCallback)(void);
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern BOOL func_ov001_02072040(void);
extern void RefreshModeWindow(s32 value);
extern void SetFieldMenuSuspended(s32 value, s32 flag);

void RunHudExitCallback(void) {
    if (data_ov001_020a04c4.context->exitCallback != NULL && func_ov001_02072040()) {
        data_ov001_020a04c4.context->exitCallback();
        RefreshModeWindow(0);
        SetFieldMenuSuspended(0, 0);
    }
}
