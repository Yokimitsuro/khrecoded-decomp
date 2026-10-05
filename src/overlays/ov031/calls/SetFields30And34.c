#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    u32 unk_30;
    u32 unk_34;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

void SetFields30And34(u32 a, u32 b)
{
    data_ov031_020bc820->unk_30 = a;
    data_ov031_020bc820->unk_34 = b;
}
