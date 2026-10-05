#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1a0];
    u32 entryFlags[4];
} SceneWork;

extern SceneWork *data_ov093_020c5100;
extern void ClearPackedBit(u32 *bitWords, int bitIndex);

void ClearEntryFlag(int flagSet, int entryIndex)
{
    ClearPackedBit(&data_ov093_020c5100->entryFlags[flagSet], entryIndex);
}
