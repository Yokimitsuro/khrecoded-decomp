#include "nitro/types.h"

extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

void CopyTileRowPair(u16 *tilemap, const u16 *src, int row, int column)
{
    u32 size;

    tilemap += row * 32;
    size = (32 - column) * 2;
    MIi_CpuCopy16(src, tilemap + column, size);
    src += 32;
    tilemap += 32;
    MIi_CpuCopy16(src, tilemap + column, size);
}
