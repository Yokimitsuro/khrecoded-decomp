#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} StageActor;

typedef struct {
    u8 pad_00[0x2c0];
    VecFx32 position;
} StageTarget;

typedef struct {
    StageActor *actor;
    u32 pad_04;
    StageTarget *target;
} StageGlobals;

typedef struct {
    u8 pad_00[0x2c];
    u16 hasResult;
    u16 pad_2e;
    s32 result;
} ScriptContext;

extern StageGlobals data_ov021_020b56c4;
extern void *GetStageMotionRecord(u16 motionId);
extern void func_ov001_02091c5c(StageTarget *target, VecFx32 *out);
extern int GetGridCellIndex(void *grid, VecFx32 *position);
extern BOOL IsGridLineClear(void *grid, int fromCell, int toCell);

int ScriptCmd_CheckTargetLineOfSight(ScriptContext *context)
{
    StageActor *actor = data_ov021_020b56c4.actor;
    StageTarget *target;
    void *grid;
    int fromCell;
    int toCell;
    VecFx32 targetPos;

    if (actor == NULL) {
        return 0;
    }
    target = data_ov021_020b56c4.target;
    if (target == NULL) {
        return 0;
    }
    grid = GetStageMotionRecord(actor->motionId);
    if (grid == NULL) {
        return 0;
    }
    if (grid == NULL) {
        return 0;
    }
    if (actor == NULL) {
        return 0;
    }
    if (target == NULL) {
        return 0;
    }
    func_ov001_02091c5c(target, &targetPos);
    fromCell = GetGridCellIndex(grid, &target->position);
    toCell = GetGridCellIndex(grid, &targetPos);
    context->hasResult = 1;
    context->result = IsGridLineClear(grid, fromCell, toCell);
    return 0;
}
