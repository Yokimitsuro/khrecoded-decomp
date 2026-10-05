#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u32 unk_44;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void DisableCategory6Objects(void);

void ResetField44(void)
{
    DisableCategory6Objects();
    data_ov031_020bc820->unk_44 = 0xffffffff;
}
