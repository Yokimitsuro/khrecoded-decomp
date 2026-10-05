#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x90];
    int pendingCount;
    u8 pad_094[4];
    int mode;
    u8 pad_09c[0xa4];
    u8 tracker[0x9c];
    u16 active;
    u8 pad_1de[6];
    void *target;
} TransitionState;

extern TransitionState *data_ov001_020a0514;
extern u32 ClearFlagIfSentinelAndReturnField(void *tracker);

BOOL IsTransitionStateDone(void)
{
    TransitionState *state = data_ov001_020a0514;

    if (state->active == 0) {
        return TRUE;
    }
    switch (state->mode) {
    case -1:
    case 0:
        return TRUE;
    case 1:
        if (ClearFlagIfSentinelAndReturnField(state->tracker) != 0) {
            return TRUE;
        }
        break;
    default:
        if (state->target == NULL) {
            if (state->pendingCount == 0) {
                return TRUE;
            }
        } else if (ClearFlagIfSentinelAndReturnField(state->tracker) != 0) {
            return TRUE;
        }
        break;
    }
    return FALSE;
}
