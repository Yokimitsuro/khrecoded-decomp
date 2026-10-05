#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    u32 unk_44;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void func_ov031_020bbedc(void);

void ResetField44(void)
{
    func_ov031_020bbedc();
    data_ov031_020bc820->unk_44 = 0xffffffff;
}
