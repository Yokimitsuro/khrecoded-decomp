#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    s32 stepIndex;
    s32 recordIndex;
    u8 pad_48[0x4];
    u32 *stepCodes;
    u8 pad_50[0x4];
    u8 stepCount;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void ReportContextError(u32 code);
extern void func_ov031_020bb5f8(void);

void AdvanceRecordStep(void)
{
    OverlayState *state;
    s32 index;

    data_ov031_020bc820->stepIndex++;
    state = data_ov031_020bc820;
    index = state->stepIndex;
    if (index < state->stepCount) {
        ReportContextError(state->stepCodes[index]);
    } else if (state->recordIndex != -1) {
        func_ov031_020bb5f8();
    } else {
        state->stepIndex = index - 1;
    }
}
