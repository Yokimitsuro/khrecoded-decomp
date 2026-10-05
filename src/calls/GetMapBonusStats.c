#include "nitro/types.h"

typedef struct PlayerStats {
    u8 data[0xe];
} PlayerStats;

typedef struct MapLayout {
    u8 pad_0000[0x32c0];
    PlayerStats bonusStats;
    PlayerStats finalStats;
} MapLayout;

extern MapLayout *gMapLayout;

PlayerStats *GetMapBonusStats(void)
{
    return &gMapLayout->bonusStats;
}
