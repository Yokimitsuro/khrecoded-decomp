#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
} SceneWork;

extern SceneWork *data_ov099_020c2900;
extern void SetPackedBit(u32 *bitWords, int bitIndex);

void SetEntryFlag_020c16d4(int flagSet, int entryIndex)
{
    SetPackedBit(data_ov099_020c2900->entryFlags[flagSet], entryIndex);
}
