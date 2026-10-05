#include "nitro/types.h"

extern u32 data_ov028_020bb3a0;
extern void PXI_Init_0202a64c();
extern void SetSoundListenersEnabled();
extern void func_ov001_02063c54(void);
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_0206a714(void);
extern void func_ov001_0206c6f4(void);

void ReleaseFieldContext(void)
{
    SetSoundListenersEnabled(0);
    PXI_Init_0202a64c(*(u32 *)(data_ov028_020bb3a0 + 0x18));
    PXI_Init_0202a64c(*(u32 *)(data_ov028_020bb3a0 + 0x1c));
    SuspendTaskAndSetFlag();
    if (*(s32 *)(data_ov028_020bb3a0 + 0x14) != -1) {
        func_ov001_0206a714();
        *(u32 *)(data_ov028_020bb3a0 + 0x14) = 0xffffffff;
    }
    func_ov001_0206c6f4();
    func_ov001_02063c54();
    data_ov028_020bb3a0 = 0;
}
