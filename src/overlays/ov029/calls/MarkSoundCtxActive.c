#include "nitro/types.h"

extern u32 data_ov029_020babc0;
extern void RestoreSessionActors();

int MarkSoundCtxActive(void)
{
    RestoreSessionActors();
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) | 0x8000;
    return 2;
}
