#include "nitro/types.h"

extern u32 data_ov029_020babc0;
extern void SetSoundListenersEnabled();
extern void PXI_Init_0202a64c();
extern void func_ov001_02063c54();

void ShutdownOv029SoundCtx(void)
{
    SetSoundListenersEnabled(0);
    PXI_Init_0202a64c(*(u32 *)(data_ov029_020babc0 + 0xc));
    PXI_Init_0202a64c(*(u32 *)(data_ov029_020babc0 + 0x10));
    func_ov001_02063c54();
    data_ov029_020babc0 = 0;
}
