#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptContext {
    u8 pad0[0x34];
    VecFx32 position;
} ScriptContext;

typedef struct ActiveContext {
    void *stage;
    int pad4;
    void *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56c4;
extern void *ResolveTaggedValueRef(ScriptContext *context, void *value);
extern s32 TaggedValueToFixed(void *tagged);
extern void func_ov001_02091c5c(void *object, VecFx32 *pos);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

int ScriptOp_StepTowardPlayer(ScriptContext *context, u8 *operands)
{
    VecFx32 origin;
    VecFx32 target;
    VecFx32 delta;
    VecFx32 direction;
    void *tagged = ResolveTaggedValueRef(context, operands + 8);

    origin = context->position;
    func_ov001_02091c5c(data_ov021_020b56c4.object, &target);
    VEC_Subtract(&target, &origin, &delta);
    VEC_Normalize(&delta, &direction);
    VEC_MultAdd(TaggedValueToFixed(tagged), &direction, &target, &context->position);
    return 0;
}
