#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xca04];
    int recordPercent;
} EntryScene;

extern const int data_ov091_020c2cc8[];
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void ClearGlobalPackedBit(int bitIndex);
extern void SetEntryFlag(int flagSet, int entryIndex);

void SyncRecordFlags(EntryScene *scene)
{
    int i;
    int bit;
    int count;

    if (!IsGlobalPackedBitSet(0x1e17)) {
        ClearGlobalPackedBit(0x11e5);
        ClearGlobalPackedBit(0x11e7);
    }
    for (i = 0; i < 40; i++) {
        if (i == 36) {
            if (IsGlobalPackedBitSet(data_ov091_020c2cc8[i])) {
                SetGlobalPackedBit(i + 0x11c2);
                if (!IsGlobalPackedBitSet(i + 0x1272) && IsGlobalPackedBitSet(i + 0x11c2)) {
                    SetEntryFlag(2, 4);
                }
            }
            continue;
        }
        bit = data_ov091_020c2cc8[i];
        switch (i) {
        case 0:
            if (IsGlobalPackedBitSet(0xa0f) && !IsGlobalPackedBitSet(0x11eb)) {
                SetGlobalPackedBit(0x11eb);
                ClearGlobalPackedBit(0x11c2);
                ClearGlobalPackedBit(0x1272);
            }
            if (IsGlobalPackedBitSet(0xa11) && !IsGlobalPackedBitSet(0x11ec)) {
                SetGlobalPackedBit(0x11ec);
                ClearGlobalPackedBit(0x11c2);
                ClearGlobalPackedBit(0x1272);
            }
            break;
        case 1:
            if (IsGlobalPackedBitSet(0xa10) && !IsGlobalPackedBitSet(0x11ed)) {
                SetGlobalPackedBit(0x11ed);
                ClearGlobalPackedBit(0x11c3);
                ClearGlobalPackedBit(0x1273);
            }
            break;
        case 2:
            if (IsGlobalPackedBitSet(0xa10) && !IsGlobalPackedBitSet(0x11ee)) {
                SetGlobalPackedBit(0x11ee);
                ClearGlobalPackedBit(0x11c4);
                ClearGlobalPackedBit(0x1274);
            }
            break;
        case 3:
            if (IsGlobalPackedBitSet(0xa11) && !IsGlobalPackedBitSet(0x11ef)) {
                SetGlobalPackedBit(0x11ef);
                ClearGlobalPackedBit(0x11c5);
                ClearGlobalPackedBit(0x1275);
            }
            break;
        case 7:
            if (IsGlobalPackedBitSet(0xa10) && !IsGlobalPackedBitSet(0x11ea)) {
                SetGlobalPackedBit(0x11ea);
                ClearGlobalPackedBit(0x11c9);
                ClearGlobalPackedBit(0x1279);
            }
            break;
        }
        if (IsGlobalPackedBitSet(bit)) {
            SetGlobalPackedBit(i + 0x11c2);
            if (!IsGlobalPackedBitSet(i + 0x1272) && IsGlobalPackedBitSet(i + 0x11c2)) {
                SetEntryFlag(2, 4);
            }
        }
    }
    count = 0;
    for (bit = 0x11c2; bit < 0x11c2 + 46; bit++) {
        if (IsGlobalPackedBitSet(bit)) {
            count++;
        }
    }
    scene->recordPercent = count * 100 / 46;
}
