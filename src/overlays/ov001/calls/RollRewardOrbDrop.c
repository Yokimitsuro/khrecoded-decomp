#include "nitro/types.h"

typedef struct OrbRange {
    u16 min;
    u16 max;
} OrbRange;

typedef struct OrbDropEntry {
    s8 chance;
    s8 pickOne;
    u8 pad_02[2];
    OrbRange ranges[6];
} OrbDropEntry;

typedef struct OrbDropTable {
    u8 pad_00[4];
    OrbDropEntry entries[1];
} OrbDropTable;

typedef struct FieldState {
    u8 pad_000[0x20f];
    u8 lowFlag : 1;
    u8 requireCheck : 1;
    u8 highFlags : 6;
    OrbDropTable *dropTable;
} FieldState;

extern FieldState *data_ov001_020a0484;
extern unsigned int func_0202a9e4(unsigned int range);
extern BOOL func_ov001_0206685c(void);
extern void SpawnRewardOrbs(u16 *amounts, u32 arg3, u32 arg4);

void RollRewardOrbDrop(int dropIndex, u32 arg)
{
    FieldState *field = data_ov001_020a0484;
    OrbDropEntry *entry;
    u16 amounts[6];
    int count;
    int i;
    unsigned int skip;

    if (dropIndex < 0) {
        return;
    }
    if (field->requireCheck == 1 && !func_ov001_0206685c()) {
        return;
    }
    entry = &field->dropTable->entries[dropIndex];
    if (entry->chance < (int)(func_0202a9e4(100) + 1)) {
        return;
    }
    count = 0;
    amounts[0] = 0;
    amounts[1] = 0;
    amounts[2] = 0;
    amounts[3] = 0;
    amounts[4] = 0;
    amounts[5] = 0;
    for (i = 0; i < 6; i++) {
        u16 min = entry->ranges[i].min;
        amounts[i] = min + func_0202a9e4((u16)(entry->ranges[i].max - min + 1));
        if (amounts[i] != 0) {
            count++;
        }
    }
    if (count == 0) {
        return;
    }
    if (entry->pickOne != 0) {
        skip = func_0202a9e4((u16)count);
        for (i = 0; i < 6; i++) {
            if (amounts[i] != 0) {
                if (skip != 0) {
                    amounts[i] = 0;
                }
                skip--;
            }
        }
    }
    SpawnRewardOrbs(amounts, arg, 0);
}
