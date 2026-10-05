#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x1340];
    void (*enterCallback)(void);
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;

extern void func_ov001_02072178(s32 value);
extern void func_ov001_020720cc(s32 enable);
extern void RefreshModeWindow(s32 value);
extern void SetFieldMenuSuspended(s32 value, s32 flag);

void RunHudEnterCallback(void) {
    if (data_ov001_020a04c4.context->enterCallback != NULL) {
        func_ov001_02072178(-1);
        func_ov001_020720cc(0);
        RefreshModeWindow(1);
        SetFieldMenuSuspended(1, 0);
        data_ov001_020a04c4.context->enterCallback();
    }
}
