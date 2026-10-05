#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

extern TaggedValue *ResolveTaggedValueRef(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern void func_ov001_0209cc94(u16 kind, u16 variant, VecFx32 *pos);
extern void NotifyFlaggedActor(VecFx32 *pos, u8 kind, u8 group, u8 extra);

int ScriptCmd_SpawnAtPosition(void *context, TaggedValue *operands)
{
    TaggedValue *kind;
    TaggedValue *variant;
    TaggedValue *x;
    TaggedValue *y;
    TaggedValue *z;
    VecFx32 pos;
    int mode;

    kind = ResolveTaggedValueRef(context, operands);
    variant = ResolveTaggedValueRef(context, operands + 1);
    x = ResolveTaggedValueRef(context, operands + 2);
    y = ResolveTaggedValueRef(context, operands + 3);
    z = ResolveTaggedValueRef(context, operands + 4);
    pos.x = TaggedValueToFixed(x);
    pos.y = TaggedValueToFixed(y);
    pos.z = TaggedValueToFixed(z);
    if (func_ov001_02063a24()) {
        mode = func_ov001_02063a38();
    } else {
        mode = 0;
    }
    switch (mode) {
    case 4:
        break;
    default:
        func_ov001_0209cc94(kind->value, variant->value, &pos);
        break;
    case 7:
        if (kind->value == 1) {
            NotifyFlaggedActor(&pos, kind->value, 1, 0xff);
        } else {
            NotifyFlaggedActor(&pos, kind->value, 0xff, 0xff);
        }
        break;
    }
    return 0;
}