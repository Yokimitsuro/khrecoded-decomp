#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

typedef struct {
    u8 pad_000[0x2c0];
    VecFx32 position;
} PlayerActor;

typedef struct {
    ScriptOwner *owner;
    u32 unk_04;
    PlayerActor *player;
} ScriptGlobals;

typedef struct {
    u8 pad_00[0x18];
    s32 cellCount;
    u8 pad_1c[4];
    s32 *cells;
} StageGrid;

extern ScriptGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern s32 TaggedValueToInt(TaggedValue *value);
extern StageGrid *GetStageMotionRecord(u32 id);
extern void GetGridCellCenter(StageGrid *grid, s32 cell, VecFx32 *out);

int ScriptOp_GetGridCellPosition(ScriptContext *context, TaggedValue *args)
{
    TaggedValue *index = ResolveTaggedValueRef(context, args + 1);
    PlayerActor *player = data_ov021_020b56c4.player;
    StageGrid *grid = GetStageMotionRecord(data_ov021_020b56c4.owner->motionId);

    if (grid != NULL) {
        if (index->value < grid->cellCount) {
            GetGridCellCenter(grid, grid->cells[TaggedValueToInt(index)], &context->vector);
        } else {
            context->vector = player->position;
        }
    }
    return 0;
}
