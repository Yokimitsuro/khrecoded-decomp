#include "nitro/types.h"

typedef struct StageRow {
    u8 pad_00[6];
    u16 flagsLow : 7;
    u16 pending : 1;
    u16 flagsHigh : 8;
    u8 pad_08[0x68];
    int value;
    int savedValue;
    u8 pad_78[0x150];
} StageRow;

typedef struct StageData {
    u8 pad_00000[0x210];
    StageRow *rows;
    u8 pad_00214[0x18bd2];
    u16 groupCount;
} StageData;

typedef struct StageGroup {
    u8 pad_00[2];
    u16 state;
    u8 pad_04[6];
    s16 firstRow;
    s16 lastRow;
    u8 active;
} StageGroup;

extern StageData *data_ov001_020a0528;
extern StageGroup *GetStageObjectHandle(u32 id);

void ResetGroupRows(u32 index)
{
    StageData *stage = data_ov001_020a0528;
    StageGroup *group;
    int row;

    if (index >= stage->groupCount) {
        return;
    }
    group = GetStageObjectHandle((u16)(index + 1));
    if (group == NULL) {
        return;
    }
    if (group != NULL) {
        for (row = group->firstRow; row <= group->lastRow; row++) {
            stage->rows[row].value = stage->rows[row].savedValue;
            stage->rows[row].pending = 0;
        }
        group->active = 0;
        if (group->state == 7) {
            group->state = 6;
        }
    }
}
