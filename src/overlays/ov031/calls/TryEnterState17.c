#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern u32 IsScreenModeIdle(void);

u32 TryEnterState17(void)
{
    u32 result;

    result = IsScreenModeIdle();
    if (result != 0) {
        data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x8000;
        return 0x11;
    }
    return 0xffffffff;
}
