#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldActor {
    u8 pad_000[0x2a4];
    fx32 sideSpeed;
} FieldActor;

extern const VecFx32 data_ov001_020a0254;
extern fx32 ApplyActorScaleFactors(FieldActor *actor);
extern int FX_Mul(int left, int right);
extern fx32 func_01ffaff4(const VecFx32 *source, VecFx32 *dest);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void AddActorSideOffset(FieldActor *actor, VecFx32 *position, const VecFx32 *direction)
{
    VecFx32 forward = *direction;
    VecFx32 side;
    fx32 scale = ApplyActorScaleFactors(actor);

    if (actor->sideSpeed != 0) {
        scale = FX_Mul(actor->sideSpeed, scale);
        func_01ffaff4(&forward, &forward);
        VEC_CrossProduct(&forward, &data_ov001_020a0254, &side);
        VEC_MultAdd(scale, &side, position, position);
    }
}
