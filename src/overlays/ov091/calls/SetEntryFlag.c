#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xcbc0];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *data_ov091_020c3740;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag(int flagSet, int entryIndex)
{
    SetPackedBit(&data_ov091_020c3740->entryFlags[flagSet], entryIndex);
}
