#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u8 *data_0205fe0c;
extern int ReadGlobalPackedBits(int address, int count);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void StoreSessionDifficultyPreset(void)
{
    u32 sessionBase = data_ov001_020a0480;
    int mode = ReadGlobalPackedBits(0x1a00, 2);

    if (mode != 3)
    {
        int offset = mode * 0xf00 + 0x3300;
        MIi_CpuCopyFast((void *)(sessionBase + 0x28), data_0205fe0c + (offset / 32) * 4, 0x1e0);
    }
}
