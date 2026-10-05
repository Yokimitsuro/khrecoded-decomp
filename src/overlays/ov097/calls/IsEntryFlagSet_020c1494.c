#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern u32 GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex)
{
    return GetPackedBitMask(&data_ov097_020c2540->entryFlags[flagSet], entryIndex) != 0;
}
