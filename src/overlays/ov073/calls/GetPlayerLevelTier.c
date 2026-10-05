#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28d5];
    s8 stageId;
} SaveData;

typedef struct PlayerStats {
    u8 pad_00[0xa];
    u16 level;
} PlayerStats;

typedef struct TierThresholds {
    int values[4];
} TierThresholds;

extern SaveData *data_0205fe0c;
extern const TierThresholds data_ov073_020c40b0;
extern u8 func_ov001_02068084(void);
extern BOOL func_ov001_020645c8(int flagId);
extern PlayerStats *GetSelectionPackedValueBlock(void);

int GetPlayerLevelTier(void)
{
    TierThresholds thresholds = data_ov073_020c40b0;
    u8 mode = func_ov001_02068084();
    s8 stageId = data_0205fe0c->stageId;
    PlayerStats *stats;
    int i;

    if (mode == 3 && stageId != 0x1d && stageId != 0x1e) {
        return 0;
    }
    if (mode == 5 && func_ov001_020645c8(0x3520)) {
        return 0;
    }
    stats = GetSelectionPackedValueBlock();
    for (i = 0; i < 3; i++) {
        if (thresholds.values[i] > stats->level) {
            break;
        }
    }
    return i;
}
