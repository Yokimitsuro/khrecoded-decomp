#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    s32 unk_10;
    u32 pxiChannel;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void SetSoundListenersEnabled(int flag);
extern void FreeSceneRecords(void);
extern void PXI_Init_0202a64c(u32 channel);
extern void SuspendTaskAndSetFlag(void);
extern void func_ov001_0206a714(void);
extern void func_ov001_0206c6f4(void);
extern void func_ov001_02063c54(void);

/* Tears down the active overlay state. */
void ShutdownActiveState(void)
{
    SetSoundListenersEnabled(0);
    FreeSceneRecords();
    PXI_Init_0202a64c(data_ov031_020bc820->pxiChannel);
    SuspendTaskAndSetFlag();
    if (data_ov031_020bc820->unk_10 != -1) {
        func_ov001_0206a714();
        data_ov031_020bc820->unk_10 = -1;
    }
    func_ov001_0206c6f4();
    func_ov001_02063c54();
    data_ov031_020bc820 = 0;
}
