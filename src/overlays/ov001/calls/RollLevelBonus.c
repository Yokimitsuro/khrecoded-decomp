#include "nitro/types.h"

typedef struct BonusCounter {
    u16 value;
    u8 pending;
} BonusCounter;

extern s16 data_ov001_0209da68[3][3];
extern u32 func_0202a9e4(u32 range);

void RollLevelBonus(int level, BonusCounter *counter)
{
    int index;
    int tier = 0;
    int bonus = 3;
    int roll = func_0202a9e4(100);
    int total = 0;

    if (level >= 60) {
        tier = 2;
    } else if (level >= 30) {
        tier = 1;
    }
    for (index = 0; index < 3; index++) {
        total += data_ov001_0209da68[tier][index];
        if (roll < total) {
            bonus = index;
            break;
        }
    }
    counter->value += (u16)bonus;
    counter->pending = 0;
}
