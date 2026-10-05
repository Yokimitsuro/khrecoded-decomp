#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int *bits;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void ClearPackedBit(int *bitWords, int bitIndex);

void ClearGlobalPackedBit(int bitIndex)
{
    ClearPackedBit(data_0205fe00.bits, bitIndex);
}
