#include "nitro/types.h"

typedef struct LevelEntry {
    u16 base;
    u8 statA;
    u8 statB;
    u8 statC;
    u8 pad_05[7];
} LevelEntry;

typedef struct LevelStats {
    u8 unk_00;
    u8 level;
    u16 unk_02;
    u16 base;
    u16 statA;
    u16 statB;
    u16 statC;
    u16 unk_0C;
} LevelStats;

extern LevelEntry data_02060f20[];

void LoadLevelStats(u32 level, LevelStats *stats)
{
    if (level >= 99) {
        level = 98;
    }
    stats->level = level;
    stats->base = data_02060f20[level].base;
    stats->statA = data_02060f20[level].statA;
    stats->statB = data_02060f20[level].statB;
    stats->statC = data_02060f20[level].statC;
    stats->unk_02 = 0;
    stats->unk_0C = 0;
}
