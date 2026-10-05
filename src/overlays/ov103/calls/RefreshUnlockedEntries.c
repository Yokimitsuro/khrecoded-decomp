#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetEntryFlag_020c01cc(int flagSet, int entryIndex);

void RefreshUnlockedEntries(void)
{
    int i;
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 10:
            if (IsGlobalPackedBitSet(0xf4c) || IsGlobalPackedBitSet(0x1150)) {
                SetEntryFlag_020c01cc(0, i);
            }
            if ((IsGlobalPackedBitSet(0xf4c) || IsGlobalPackedBitSet(0x1150)) && !IsGlobalPackedBitSet(0xf4e)) {
                SetEntryFlag_020c01cc(1, i);
            }
            break;
        case 8:
            if (IsGlobalPackedBitSet(0xf4d) || IsGlobalPackedBitSet(0x1151)) {
                SetEntryFlag_020c01cc(0, i);
            }
            if (IsGlobalPackedBitSet(0xf4d) || IsGlobalPackedBitSet(0x1151)) {
                IsGlobalPackedBitSet(0xf4f);
            }
            break;
        default:
            if (IsGlobalPackedBitSet(0xbea)) {
                SetEntryFlag_020c01cc(0, i);
            }
            break;
        }
    }
}
