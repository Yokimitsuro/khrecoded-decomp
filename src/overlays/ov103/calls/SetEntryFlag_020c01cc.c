#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *data_ov103_020c0720;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c01cc(int flagSet, int entryIndex)
{
    SetPackedBit(&data_ov103_020c0720->entryFlags[flagSet], entryIndex);
}
