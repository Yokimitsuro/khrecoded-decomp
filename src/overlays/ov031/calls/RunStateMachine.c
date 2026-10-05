#include "nitro/types.h"

typedef s32 (*StateHandler)(void);

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x10];
    s32 current;
    u8 pad_1c[0xa0];
    s32 frameCount;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern StateHandler data_ov031_020bc7b8[];
extern void ApplyOverlayScaleMode_020bab40(int mode);
extern void LeaveState(void);

s32 RunStateMachine(void)
{
    s32 next;

    data_ov031_020bc820->frameCount++;
    do {
        data_ov031_020bc820->flags &= 0x7fff;
        next = data_ov031_020bc7b8[data_ov031_020bc820->current]();
        if (next >= 0) {
            data_ov031_020bc820->current = next;
        }
    } while (data_ov031_020bc820->flags & 0x8000);
    if (data_ov031_020bc820->flags & 8) {
        ApplyOverlayScaleMode_020bab40(0);
    }
    if (data_ov031_020bc820->flags & 4) {
        LeaveState();
    }
    return 0;
}
