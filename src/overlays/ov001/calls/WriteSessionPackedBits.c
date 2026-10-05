#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern void WritePackedBits(u32 *base, u32 bitOffset, u32 bitCount, u32 value);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value)
{
    if (bitOffset >= 0x3300)
    {
        WritePackedBits((u32 *)(data_ov001_020a0480 + 0x28), bitOffset - 0x3300, bitCount, value);
        return;
    }
    WriteGlobalPackedBits(bitOffset, bitCount, value);
}
