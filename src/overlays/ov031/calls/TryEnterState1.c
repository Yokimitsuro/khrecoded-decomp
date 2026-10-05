#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 func_ov001_02063620(void);
extern u32 PushVramState(void);

u32 TryEnterState1(void)
{
    u32 result;

    result = func_ov001_02063620();
    if (result != 0) {
        return 0xffffffff;
    }
    PushVramState();
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
    return 1;
}
