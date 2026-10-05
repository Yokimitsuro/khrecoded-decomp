#include "nitro/types.h"

extern u16 data_ov001_0209e0f4[][4];
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void WritePackedRecord(int row, int column, u32 value)
{
    WriteGlobalPackedBits(data_ov001_0209e0f4[row][column], 0x14, value);
}
