#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptContext {
    u8 pad0[0x2c];
    u16 resultType;
    u8 pad2e[2];
    fx32 result;
} ScriptContext;

typedef struct ActiveContext {
    void *stage;
    void *source;
    void *object;
} ActiveContext;

extern ActiveContext data_ov021_020b56c4;
extern void NotifySceneObjectHandler(void *object, VecFx32 *pos);
extern VecFx32 *func_ov001_02090f2c(void *object);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);

int ScriptOp_GetPlayerHorizontalDrift(ScriptContext *context)
{
    VecFx32 position;
    VecFx32 anchor;
    VecFx32 delta;
    void *object = data_ov021_020b56c4.object;

    if (object == NULL) {
        return 0;
    }
    NotifySceneObjectHandler(object, &position);
    anchor = *func_ov001_02090f2c(object);
    VEC_Subtract(&position, &anchor, &delta);
    delta.y = 0;
    context->resultType = 0x10;
    context->result = VEC_Mag(&delta) - 0xe66;
    if (context->result < 0) {
        context->result = 0;
    }
    return 0;
}
