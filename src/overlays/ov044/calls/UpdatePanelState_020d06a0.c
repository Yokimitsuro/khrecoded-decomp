#include "nitro/types.h"

extern u32 data_ov044_020d0ec0;

extern void func_ov044_020d034c(void);
extern void UpdatePanelCamera(void);

u32 UpdatePanelState_020d06a0(void)
{
    s32 prevState = *(s32 *)(data_ov044_020d0ec0 + 0x40);
    s32 state = *(s32 *)(data_ov044_020d0ec0 + 0x44);

    if (prevState != state || prevState == 6) {
        func_ov044_020d034c();
    }
    UpdatePanelCamera();
    return 0;
}
