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

extern void SetFieldCaptionText(s32 value);
extern void UpdateFieldFlag18(s32 enable);
extern void RefreshModeWindow(s32 value);
extern void SetFieldMenuSuspended(s32 value, s32 flag);

void RunHudEnterCallback(void) {
    if (data_ov001_020a04c4.context->enterCallback != NULL) {
        SetFieldCaptionText(-1);
        UpdateFieldFlag18(0);
        RefreshModeWindow(1);
        SetFieldMenuSuspended(1, 0);
        data_ov001_020a04c4.context->enterCallback();
    }
}
