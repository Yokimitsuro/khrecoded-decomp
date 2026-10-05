#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
} SceneWork;

extern SceneWork *data_ov099_020c2900;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL IsEntryFlagSet_020c16ac(int flagSet, int entryIndex)
{
    return GetPackedBitMask(data_ov099_020c2900->entryFlags[flagSet], entryIndex) != 0;
}
