#include "nitro/types.h"

typedef struct SavedStateOwner
{
    u8 pad_00[0x44];
    u16 bitOffset;
    u8 bitCount;
} SavedStateOwner;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);

u16 GetSavedStateValue(SavedStateOwner *owner)
{
    return (ReadSessionPackedBits(owner->bitOffset, owner->bitCount) & 0xFFFE) >> 1;
}
