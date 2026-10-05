#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x8];
    u32 entryFlags[1];
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c14c0(int flagSet, int entryIndex)
{
    SetPackedBit(&data_ov097_020c2540->entryFlags[flagSet], entryIndex);
}
