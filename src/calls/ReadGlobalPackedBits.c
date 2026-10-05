#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 *bits;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern u32 ReadPackedBitField(u32 *words, u32 startBit, u32 fieldWidth);

u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount)
{
    return ReadPackedBitField(data_0205fe00.bits, bitOffset, bitCount);
}
