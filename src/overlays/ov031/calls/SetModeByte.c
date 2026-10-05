#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    u8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

void SetModeByte(u8 mode)
{
    data_ov031_020bc820->mode = mode;
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x4000;
}
