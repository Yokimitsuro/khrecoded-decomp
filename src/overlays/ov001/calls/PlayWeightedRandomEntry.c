#include "nitro/types.h"

typedef struct WeightedEntry {
    s16 id;
    s8 weight;
    u8 pad_03;
} WeightedEntry;

typedef struct WeightedTable {
    u8 count;
    u8 pad_01[3];
    WeightedEntry entries[1];
} WeightedTable;

typedef struct WeightedTableFile {
    u8 count;
    u8 pad_01[3];
    WeightedTable *tables[1];
} WeightedTableFile;

typedef struct WeightedTableHolder {
    WeightedTableFile *file;
} WeightedTableHolder;

typedef struct GameState {
    u8 pad_0000[0x2878];
    u32 difficulty : 2;
    u32 flagsHigh : 30;
} GameState;

extern WeightedTableHolder *data_ov001_020a049c;
extern GameState *data_0205fe0c;

extern u32 func_0202a9e4(u32 range);
extern u32 func_ov001_020664f0(u32 arg1, u32 arg2, u32 arg3, u32 arg4);

void PlayWeightedRandomEntry(int tableIndex, u32 arg)
{
    WeightedTableHolder *holder = data_ov001_020a049c;
    int i;
    int roll;
    WeightedTable *table;
    s32 chosen;
    u32 difficulty;
    int total;

    if (tableIndex < 0) {
        return;
    }
    table = holder->file->tables[tableIndex];
    difficulty = data_0205fe0c->difficulty;
    chosen = -1;
    total = 0;
    roll = func_0202a9e4(100) + 1;
    for (i = 0; i < table->count; i++) {
        total += (&table->entries[difficulty])[i].weight;
        if (roll <= total) {
            chosen = (&table->entries[difficulty])[i].id;
            break;
        }
    }
    func_ov001_020664f0(6, chosen, arg, 0);
}
