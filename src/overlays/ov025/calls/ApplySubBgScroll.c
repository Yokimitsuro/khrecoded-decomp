#include "nitro/types.h"

extern void *data_ov025_020b7780;
extern int func_ov025_020b7600(void *field);

void ApplySubBgScroll(void) {
    u32 offset = func_ov025_020b7600((u8 *)data_ov025_020b7780 + 0x64f4) & 0x1ff;
    *(vu32 *)0x04001018 = offset;
    *(vu32 *)0x0400101c = offset;
}
