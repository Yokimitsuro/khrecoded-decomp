#include "nitro/types.h"

typedef struct SavedStateOwner
{
    u8 pad_00[0x44];
    u16 bitOffset;
    u8 bitCount;
} SavedStateOwner;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void SetSavedStateValue(SavedStateOwner *owner, u16 value)
{
    WriteSessionPackedBits(owner->bitOffset, owner->bitCount,
                                    (ReadSessionPackedBits(owner->bitOffset, owner->bitCount) & 0xFFFF0001) | (value << 1));
}
