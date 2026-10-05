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

extern TaggedValue *ResolveTaggedValueRef(ScriptContext *context, TaggedValue *value);
extern fx32 TaggedValueToFixed(TaggedValue *tagged);
extern int nextRandom12(void);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptCmd_PushRandomSpherical(ScriptContext *context, u8 *args)
{
    TaggedValue *minRef;
    fx32 range;
    fx32 minDist;
    VecFx32 dir;

    minRef = ResolveTaggedValueRef(context, (TaggedValue *)(args + 8));
    range = TaggedValueToFixed(ResolveTaggedValueRef(context, (TaggedValue *)(args + 0x10)));
    range -= TaggedValueToFixed(minRef);
    dir.x = nextRandom12() - 0x800;
    dir.y = nextRandom12() - 0x800;
    dir.z = nextRandom12() - 0x800;
    if (VEC_Mag(&dir) == 0) {
        dir.z = 0x1000;
    }
    func_01ffaff4(&dir, &dir);
    minDist = TaggedValueToFixed(minRef);
    VEC_MultAdd(minDist + FX_Mul(range, nextRandom12()), &dir, &context->position, &context->position);
    return 0;
}
