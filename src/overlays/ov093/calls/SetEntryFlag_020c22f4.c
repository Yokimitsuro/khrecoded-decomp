#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xd1a0];
    u32 entryFlags[4];
} SceneWork;

extern SceneWork *data_ov093_020c5100;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c22f4(int flagSet, int entryIndex)
{
    SetPackedBit(&data_ov093_020c5100->entryFlags[flagSet], entryIndex);
}
