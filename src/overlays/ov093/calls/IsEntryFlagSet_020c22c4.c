#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1a0];
    u32 entryFlags[4];
} SceneWork;

extern SceneWork *data_ov093_020c5100;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex)
{
    return GetPackedBitMask(&data_ov093_020c5100->entryFlags[flagSet], entryIndex) != 0;
}
