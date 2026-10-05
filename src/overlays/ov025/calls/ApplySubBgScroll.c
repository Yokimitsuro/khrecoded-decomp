#include "nitro/types.h"

extern void *data_ov025_020b7780;
extern int NegateFieldValue(void *field);

void ApplySubBgScroll(void) {
    u32 offset = NegateFieldValue((u8 *)data_ov025_020b7780 + 0x64f4) & 0x1ff;
    *(vu32 *)0x04001018 = offset;
    *(vu32 *)0x0400101c = offset;
}
