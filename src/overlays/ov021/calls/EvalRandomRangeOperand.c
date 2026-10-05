#include "nitro/types.h"

extern u32 random_next_scaled();

/* Evaluates a random-range script operand. */
u32 EvalRandomRangeOperand(s32 result, s32 range)
{
    s32 rolled;

    *(u16 *)(result + 0x2c) = 1;
    rolled = random_next_scaled((*(s32 *)(range + 0xc) - *(s32 *)(range + 4)) + 1);
    *(s32 *)(result + 0x30) = *(s32 *)(range + 4) + rolled;
    return 0;
}
