#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_02063848(u32 a, u32 b);
extern u32 func_ov001_02067f8c(u32 a);
extern u32 func_ov001_02067f9c(void);
extern u32 func_ov001_0206e644(void);

u32 EnterState7Alt(void)
{
    OverlayState *state;
    u32 a;
    u32 b;

    state = data_ov031_020bc820;
    a = func_ov001_0206e644();
    b = func_ov001_02067f9c();
    a = func_ov001_02067f8c(a);
    func_ov001_02063848(b, a);
    state->flags = state->flags | 2;
    return 7;
}
