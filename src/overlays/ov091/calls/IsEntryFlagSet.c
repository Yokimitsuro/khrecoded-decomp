#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xcbc0];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *data_ov091_020c3740;
extern u32 GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet(int flagSet, int entryIndex)
{
    return GetPackedBitMask(&data_ov091_020c3740->entryFlags[flagSet], entryIndex) != 0;
}
