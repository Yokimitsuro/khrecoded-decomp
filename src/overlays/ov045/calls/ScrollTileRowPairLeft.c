#include "nitro/types.h"

extern void MI_CpuMove16(const void *src, void *dst, u32 size);
extern void MIi_CpuClear16(u16 value, void *dst, u32 size);

void ScrollTileRowPairLeft(u16 *tilemap, int row, int shift)
{
    tilemap += row * 32;
    MI_CpuMove16(tilemap + shift, tilemap, (64 - shift) * 2);
    MIi_CpuClear16(0, tilemap + (32 - shift), shift * 2);
    MIi_CpuClear16(0, tilemap + (64 - shift), shift * 2);
}
