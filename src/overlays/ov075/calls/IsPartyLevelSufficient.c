#include "nitro/types.h"

typedef struct {
    s32 values[4];
} LevelThresholds;

typedef struct {
    u8 pad_00[4];
    u16 members[3];
    u16 level;
} PartyInfo;

extern const LevelThresholds data_ov075_020d1684;
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern PartyInfo *GetSelectionPackedValueBlock(void);
extern s8 func_ov001_02068084(void);
extern BOOL func_ov001_020645c8(u32 value);

BOOL IsPartyLevelSufficient(void)
{
    LevelThresholds thresholds = data_ov075_020d1684;
    u32 progress = ReadSessionPackedBits(0x1a00, 2);
    PartyInfo *party = GetSelectionPackedValueBlock();
    int count;

    if (func_ov001_02068084() == 5 && progress != 2) {
        if (!func_ov001_020645c8(0x3609) || !func_ov001_020645c8(0x360a)) {
            return TRUE;
        }
        if (party->level >= 0xce4) {
            return TRUE;
        }
        return FALSE;
    }
    for (count = 0; count < 3; count++) {
        if (party->members[count] == 0xffff) {
            break;
        }
    }
    if (party->level >= thresholds.values[count]) {
        return TRUE;
    }
    return FALSE;
}
