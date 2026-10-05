#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int unlockBit;
    u8 pad_30[4];
} MenuEntryDef;

typedef struct {
    u8 pad_0000[0xf0cc];
    int lastUnlockedEntry;
} MenuScene;

extern MenuEntryDef data_ov097_020c2144[];
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetEntryFlag_020c14c0(int flagSet, int entryIndex);

void SyncUnlockedEntryFlags(MenuScene *scene)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (IsGlobalPackedBitSet(data_ov097_020c2144[i].unlockBit)) {
            SetEntryFlag_020c14c0(0, i);
            scene->lastUnlockedEntry = i + 1;
            SetGlobalPackedBit(i + 0x11b2);
        }
        if (!IsGlobalPackedBitSet(i + 0x1262) && IsGlobalPackedBitSet(i + 0x11b2)) {
            SetEntryFlag_020c14c0(1, i);
        }
    }
}
