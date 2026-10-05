#include "nitro/types.h"

extern void SetBit1WhenBit0Set(u32 *flags, s32 enable);

void SetSubModelsEnabled(int entity, int enable)
{
    int i;
    for (i = 0; i < 2; i++) {
        SetBit1WhenBit0Set((u32 *)(entity + 0xb68 + i * 0x230), enable);
    }
    if (enable == 0) {
        *(u64 *)(entity + 0x9ac) &= ~(u64)0x40;
    } else {
        *(u64 *)(entity + 0x9ac) |= 0x40;
    }
}
