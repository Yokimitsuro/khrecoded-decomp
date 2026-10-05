#include "nitro/types.h"

extern BOOL func_ov001_020645c8(u32 flagIndex);
extern u32 func_0202a9e4(u16 range);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

BOOL PickRandomUnsetSessionFlag(void)
{
    u32 candidates[16];
    int count = 0;
    int i;
    u32 value;

    for (i = 0; i < 16; i++) {
        if (!func_ov001_020645c8(i + 0x3700)) {
            candidates[count] = i;
            count++;
        }
    }
    value = candidates[func_0202a9e4(count)];
    WriteSessionPackedBits(0x352f, 4, value);
    return TRUE;
}
