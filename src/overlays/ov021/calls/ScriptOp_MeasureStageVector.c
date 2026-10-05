#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x2c];
    u16 resultTag;
    u16 pad_2e;
    fx32 resultValue;
} ScriptContext;

typedef struct StageManager {
    u8 pad_00000[0x18e60];
    VecFx32 vectors[1];
} StageManager;

extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern StageManager *func_ov001_0209c3e8(void);
extern fx32 func_01ffaff4(const VecFx32 *a, const VecFx32 *b);

int ScriptOp_MeasureStageVector(ScriptContext *context, TaggedValue *operand)
{
    TaggedValue *index = ResolveTaggedValueRef(context, operand);
    StageManager *manager = func_ov001_0209c3e8();
    context->resultTag = 0x10;
    s32 slot = index->value;
    context->resultValue = func_01ffaff4(&manager->vectors[slot], (VecFx32 *)&manager->vectors[slot].x);
    return 0;
}
