#include "nitro/types.h"

extern u32 data_ov030_020bd020;
extern void SetSoundListenersEnabled(u32 arg);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void PXI_Init_0202a64c(u32 channel);
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_0206a714(void);
extern void func_ov001_0206c6f4(void);
extern void func_ov001_02063c54(void);

void MoviePlayer_Close(void)
{
    SetSoundListenersEnabled(0);
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov030_020bd020 + 0x30));
    PXI_Init_0202a64c(*(u32 *)(data_ov030_020bd020 + 0x18));
    PXI_Init_0202a64c(*(u32 *)(data_ov030_020bd020 + 0x1c));
    SuspendTaskAndSetFlag();
    if (*(s32 *)(data_ov030_020bd020 + 0x14) != -1) {
        func_ov001_0206a714();
        *(u32 *)(data_ov030_020bd020 + 0x14) = 0xffffffff;
    }
    func_ov001_0206c6f4();
    func_ov001_02063c54();
    data_ov030_020bd020 = 0;
}
