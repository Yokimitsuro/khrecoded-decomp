#include "nitro/types.h"

extern int GetPlayerEntryCount(int player, u32 id);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

BOOL UpdateEntryCountRecord(void)
{
    u32 count = GetPlayerEntryCount(0, 9);

    if (!IsPlayerEntryFlagSet(0, 9)) {
        return FALSE;
    }
    if (count > ReadSessionPackedBits(0x1a42, 3)) {
        WriteSessionPackedBits(0x1a42, 3, count);
        return count != 1;
    }
    return FALSE;
}
