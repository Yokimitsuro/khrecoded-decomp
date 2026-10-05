#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 *bits;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void WritePackedBits(u32 *base, u32 bitOffset, u32 bitCount, u32 value);

void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value)
{
    WritePackedBits(data_0205fe00.bits, bitOffset, bitCount, value);
}
