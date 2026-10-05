#include "nitro/types.h"

extern int GetPackedBitMask();

/* Second argument is forwarded to the callee unchanged. */
BOOL IsPackedBitSet(u8 *base, int bitIndex)
{
    return GetPackedBitMask(base + 0xc, bitIndex) != 0;
}
