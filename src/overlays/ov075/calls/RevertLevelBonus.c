#include "nitro/types.h"

typedef struct UnitStats {
    u8 pad_00;
    u8 level;
    u8 pad_02[2];
    u16 hp;
    u16 attack;
    u16 magic;
    u16 defense;
    u16 luck;
} UnitStats;

typedef struct LevelBonus {
    u8 pad_00[0x1a];
    u8 level;
    s8 hp;
    s8 attack;
    s8 magic;
    s8 defense;
    s8 luck;
} LevelBonus;

void RevertLevelBonus(UnitStats *stats, const LevelBonus *bonus, int count)
{
    do {
        stats->level -= bonus->level;
        stats->hp -= bonus->hp;
        stats->attack -= bonus->attack;
        stats->magic -= bonus->magic;
        stats->defense -= bonus->defense;
        stats->luck -= bonus->luck;
    } while (--count != 0);
}