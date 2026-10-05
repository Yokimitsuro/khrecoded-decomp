#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

void SetFlagBit4(int enable)
{
    if (enable != 0) {
        data_ov031_020bc820->flags = data_ov031_020bc820->flags | 4;
        return;
    }
    data_ov031_020bc820->flags = data_ov031_020bc820->flags & 0xfffb;
}
