#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageInfo {
    u8 pad0[0x16];
    u16 stageId;
} StageInfo;

typedef struct GridContext {
    StageInfo *stage;
    int pad4;
    void *object;
} GridContext;

typedef struct GridSample {
    u8 pad0[0x2c];
    u16 valid;
    u8 pad2e[2];
    u32 value;
} GridSample;

extern GridContext data_ov021_020b56c4;
extern void *GetStageMotionRecord(u32 id);
extern void NotifySceneObjectHandler(void *object, VecFx32 *pos);
extern int GetGridCellIndex(void *grid, VecFx32 *position);
extern u8 func_ov006_020a14e0(void *table, int index);

int SampleGridCellValue(GridSample *sample)
{
    StageInfo *stage = data_ov021_020b56c4.stage;
    void *object;
    void *table;
    VecFx32 pos;
    int index;

    if (stage == NULL) {
        return 0;
    }
    object = data_ov021_020b56c4.object;
    if (object == NULL) {
        return 0;
    }
    table = GetStageMotionRecord(stage->stageId);
    if (table == NULL) {
        return 0;
    }
    NotifySceneObjectHandler(object, &pos);
    index = GetGridCellIndex(table, &pos);
    sample->valid = 1;
    sample->value = func_ov006_020a14e0(table, index);
    return 0;
}
