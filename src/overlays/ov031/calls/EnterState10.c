#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void func_ov001_0206a72c(int mode);

u32 EnterState10(void)
{
    OverlayState *state;

    state = data_ov031_020bc820;
    func_ov001_0206a72c((int)data_ov031_020bc820->mode);
    state->flags = state->flags | 0x20;
    return 10;
}
