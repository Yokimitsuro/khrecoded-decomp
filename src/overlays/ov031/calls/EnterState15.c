#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void StartIdleSceneObjects(void);
extern void func_ov001_02087650(u32 a);

u32 EnterState15(void)
{
    OverlayState *state;

    state = data_ov031_020bc820;
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x20;
    if ((state->flags & 0x10) == 0) {
        StartIdleSceneObjects();
        func_ov001_02087650(1);
    }
    return 0xf;
}
