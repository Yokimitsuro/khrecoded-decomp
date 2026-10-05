#include "nitro/types.h"

typedef struct StageVector {
    s32 x;
    s32 y;
    s32 z;
} StageVector;

typedef struct StageManager {
    u8 pad_00000[0x18e60];
    StageVector vectors[1];
} StageManager;

typedef struct ScriptRecord {
    u8 pad_00[4];
    s32 index;
} ScriptRecord;

extern StageManager *func_ov001_0209c3e8(void);
extern u32 ResolveTaggedValueRef(u32 context, int operand);
extern s32 TaggedValueToFixed(u32 tagged);

u32 ScriptOp_SubtractStageVector(u32 context, int operands)
{
    ScriptRecord *record = (ScriptRecord *)ResolveTaggedValueRef(context, operands);
    u32 xValue = ResolveTaggedValueRef(context, operands + 8);
    u32 yValue = ResolveTaggedValueRef(context, operands + 0x10);
    u32 zValue = ResolveTaggedValueRef(context, operands + 0x18);
    StageManager *manager = func_ov001_0209c3e8();

    manager->vectors[record->index].x -= TaggedValueToFixed(xValue);
    manager->vectors[record->index].y -= TaggedValueToFixed(yValue);
    manager->vectors[record->index].z -= TaggedValueToFixed(zValue);
    return 0;
}
