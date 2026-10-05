#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageManager {
    u8 pad0[0x18e50];
    VecFx32 offset;
} StageManager;

extern void *ResolveTaggedValueRef(void *context, void *value);
extern s32 TaggedValueToFixed(void *tagged);
extern StageManager *func_ov001_0209c3e8(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

int ScriptOp_AddStageOffset(void *context, u8 *operands)
{
    VecFx32 delta;
    void *tagX = ResolveTaggedValueRef(context, operands);
    void *tagY = ResolveTaggedValueRef(context, operands + 8);
    void *tagZ = ResolveTaggedValueRef(context, operands + 0x10);
    StageManager *stage = func_ov001_0209c3e8();

    delta.x = TaggedValueToFixed(tagX);
    delta.y = TaggedValueToFixed(tagY);
    delta.z = TaggedValueToFixed(tagZ);
    VEC_Add(&delta, &stage->offset, &stage->offset);
    return 0;
}
