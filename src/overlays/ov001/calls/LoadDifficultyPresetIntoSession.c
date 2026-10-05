#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u8 *data_0205fe0c;
extern int ReadGlobalPackedBits(int address, int count);
extern void MIi_CpuCopyFast(void *dst, void *src, u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);

void LoadDifficultyPresetIntoSession(void)
{
    u32 sessionBase = data_ov001_020a0480;
    int mode = ReadGlobalPackedBits(0x1a00, 2);

    if (mode != 3)
    {
        int offset = mode * 0xf00 + 0x3300;
        MIi_CpuCopyFast(data_0205fe0c + (offset / 32) * 4, (void *)(sessionBase + 0x28), 0x1e0);
        return;
    }
    MIi_CpuClearFast(0, (void *)(sessionBase + 0x28), 0x1e0);
}
