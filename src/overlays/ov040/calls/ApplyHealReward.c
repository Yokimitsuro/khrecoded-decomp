#include "nitro/types.h"

typedef struct HealthStats {
    u16 max;
    u16 current;
} HealthStats;

typedef struct RewardActor {
    u8 pad_000[0x1d4];
    HealthStats *health;
} RewardActor;

extern BOOL AddClampedHealth(RewardActor *actor, s16 delta);
extern int ShowMovieMessage3700(void);
extern int func_ov035_020bafb4(void);
extern void func_ov040_020bda8c(int entry, int amount);
extern void ApplyRewardByTier(RewardActor *actor, int kind, int tier);

void ApplyHealReward(RewardActor *actor, int kind, int tier)
{
    if (kind == 0) {
        int amount = 0;

        switch (tier) {
        case 0:
            amount = 1;
            break;
        case 1:
            amount = 10;
            break;
        case 2:
            amount = 100;
            break;
        }
        if (actor->health->current != 0 && amount > 0) {
            AddClampedHealth(actor, amount);
        }
        if (ShowMovieMessage3700() > 0 && amount > 0) {
            func_ov040_020bda8c(1, amount);
        }
        if (func_ov035_020bafb4() > 0 && amount > 0) {
            func_ov040_020bda8c(2, amount);
        }
        return;
    }
    ApplyRewardByTier(actor, kind, tier);
}

