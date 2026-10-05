#include "nitro/types.h"

typedef struct ObjectManager {
    u8 pad_000[0x120];
    u32 flagBits;
} ObjectManager;

extern ObjectManager *data_ov001_020a04f8;
extern int GetPackedBitMask(u32 *bitWords, int bitIndex);

BOOL ObjectManager_IsFlagBitSet(int bitIndex)
{
    if (GetPackedBitMask(&data_ov001_020a04f8->flagBits, bitIndex) != 0) {
        return TRUE;
    }
    return FALSE;
}
