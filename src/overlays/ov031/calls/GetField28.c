#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u32 unk_28;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

u32 GetField28(void)
{
    if (data_ov031_020bc820 != 0) {
        return data_ov031_020bc820->unk_28;
    }
    return 0;
}
