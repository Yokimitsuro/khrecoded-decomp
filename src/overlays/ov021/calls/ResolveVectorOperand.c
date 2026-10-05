#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct {
    void *actor;
    u32 pad_04;
    void *target;
} StageGlobals;

extern StageGlobals data_ov021_020b56c4;
extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern void NotifySceneObjectHandler(void *target, VecFx32 *out);
extern VecFx32 *func_ov001_02090f2c(void *target);

void ResolveVectorOperand(ScriptContext *context, TaggedValue *operand, VecFx32 *out)
{
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;

    switch (operand->value) {
    case -1:
        NotifySceneObjectHandler(data_ov021_020b56c4.target, out);
        return;
    case -2:
        *out = *func_ov001_02090f2c(data_ov021_020b56c4.target);
        return;
    case -10:
        *out = context->position;
        return;
    }
    x = ResolveTaggedValueRef(context, operand);
    y = ResolveTaggedValueRef(context, operand + 1);
    z = ResolveTaggedValueRef(context, operand + 2);
    out->x = TaggedValueToFixed(x);
    out->y = TaggedValueToFixed(y);
    out->z = TaggedValueToFixed(z);
}
