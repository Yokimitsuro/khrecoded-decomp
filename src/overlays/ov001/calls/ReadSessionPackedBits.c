#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u32 ReadPackedBitField(u32 *words, u32 startBit, u32 fieldWidth);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

u32 ReadSessionPackedBits(int bitOffset, u32 bitCount)
{
    if (bitOffset >= 0x3300) {
        return ReadPackedBitField((u32 *)(data_ov001_020a0480 + 0x28), bitOffset - 0x3300, bitCount);
    }
    return ReadGlobalPackedBits(bitOffset, bitCount);
}
