#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x18e60];
    VecFx32 points[2];
} StageState;

extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern StageState *func_ov001_0209c3e8(void);

int ScriptCmd_AddStagePoint(void *context, TaggedValue *operands)
{
    TaggedValue *slot;
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;
    StageState *stage;

    slot = ResolveTaggedValueRef(context, operands);
    x = ResolveTaggedValueRef(context, operands + 1);
    y = ResolveTaggedValueRef(context, operands + 2);
    z = ResolveTaggedValueRef(context, operands + 3);
    stage = func_ov001_0209c3e8();
    if (slot->value < 0 || slot->value > 1) {
        return 0;
    }
    stage->points[slot->value].x += TaggedValueToFixed(x);
    stage->points[slot->value].y += TaggedValueToFixed(y);
    stage->points[slot->value].z += TaggedValueToFixed(z);
    return 0;
}
