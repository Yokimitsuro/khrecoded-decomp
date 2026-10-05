#include "nitro/types.h"

extern u16 data_ov001_0209e0f4[][4];
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

u32 ReadPackedRecord(int row, int column)
{
    return ReadGlobalPackedBits(data_ov001_0209e0f4[row][column], 0x14);
}
