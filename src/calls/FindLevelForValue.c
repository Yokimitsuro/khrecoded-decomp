#include "nitro/types.h"

extern u32 GetEntryParam(u32 index);

u8 FindLevelForValue(u32 value, u32 *outRemaining)
{
    BOOL done = FALSE;
    u8 level = 0;

    do {
        u32 threshold = GetEntryParam(level);
        if (value >= threshold) {
            level++;
            if (level >= 0x31) {
                value = 0;
                done = TRUE;
            }
        } else {
            done = TRUE;
            value = threshold - value;
        }
    } while (!done);
    if (outRemaining != NULL) {
        *outRemaining = value;
    }
    return level;
}
