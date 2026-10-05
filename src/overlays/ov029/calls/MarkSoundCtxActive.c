#include "nitro/types.h"

extern u32 data_ov029_020babc0;
extern void func_ov001_02063404();

int MarkSoundCtxActive(void)
{
    func_ov001_02063404();
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) | 0x8000;
    return 2;
}
