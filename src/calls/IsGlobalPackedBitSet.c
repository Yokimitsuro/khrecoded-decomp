#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    int *bits;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern int GetPackedBitMask(int *bitWords, int bitIndex);

BOOL IsGlobalPackedBitSet(int bitIndex)
{
    if (GetPackedBitMask(data_0205fe00.bits, bitIndex) != 0) {
        return TRUE;
    }
    return FALSE;
}
